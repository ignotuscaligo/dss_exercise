#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <SDL2/SDL_image.h>

namespace
{

const utility::string_t statsapi_url   = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

const utility::string_t mlb_images_url   = U("http://mlb.mlb.com/mlb/images");
const utility::string_t background_image = U("devices/ballpark/1920x1080/1.jpg");

}

Application::Application()
: m_apiClient(statsapi_url)
, m_backgroundClient(mlb_images_url)
{
    auto logger = utility::get_logger();
    logger->info("Creating application");
}

void Application::run()
{
    auto logger = utility::get_logger();

    logger->info("Running application");

    try
    {
        m_context = std::make_shared<render::Context>();
        m_window = std::make_shared<render::Window>("DSS Exercise", 1280, 720);
        m_renderer = std::make_shared<render::Renderer>(m_window);
    }
    catch (const std::runtime_error& e)
    {
        logger->error("Failed to initialize SDL objects: {}", e.what());
    }

    m_renderer->drawColor(0, 0, 0, 255);

    SDL_Event e;
    bool quit = false;

    initialize();

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
        }

        update();

        m_renderer->clear();

        auto background = m_renderer->fetchTexture("background");

        if (background)
        {
            m_renderer->fillTexture(background);
        }

        m_renderer->present();
    }

    m_renderer.reset();
    m_window.reset();
    m_context.reset();
}

void Application::initialize()
{
    auto logger = utility::get_logger();

    logger->info("Starting cpprestsdk task");

    auto apiRequestTask = m_apiClient.request(web::http::methods::GET, web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                                                                                     .append_query(U("date"), query_date)
                                                                                                     .append_query(U("sportId"), query_sport_id)
                                                                                                     .to_string());

    auto jsonTask = apiRequestTask.then([](web::http::http_response response) {
        auto logger = utility::get_logger();

        logger->debug("Received response: {}", response.status_code());

        if (response.status_code() != 200)
        {
            throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
        }

        return response.extract_json();
    });

    m_apiTask = jsonTask.then([](web::json::value jsonObject) {
        auto logger = utility::get_logger();

        logger->debug("Processing extracted JSON");

        auto totalGames = jsonObject[U("totalGames")].as_integer();
        auto gamesList = jsonObject[U("dates")][0][U("games")];

        logger->debug("totalGames: {}", totalGames);

        for (int i = 0; i < totalGames; i++)
        {
            auto game = mlb::Game(gamesList[i]);
            logger->debug("game {0} headline: {1}", i, game.headline());
        }
    });

    m_apiTaskRunning = true;

    auto imageRequestTask = m_backgroundClient.request(web::http::methods::GET, background_image);

    m_backgroundTask = imageRequestTask.then([](web::http::http_response response) {
        auto logger = utility::get_logger();

        logger->debug("Received response: {}", response.status_code());

        if (response.status_code() != 200)
        {
            throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
        }

        return response.extract_vector();
    });

    m_backgroundTaskRunning = true;
}

void Application::update()
{
    auto logger = utility::get_logger();

    if (m_apiTaskRunning)
    {
        try
        {
            if (m_apiTask.is_done())
            {
                logger->info("API request task completed successfully");
                m_apiTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing API request: {}", e.what());
        }
    }

    if (m_backgroundTaskRunning)
    {
        try
        {
            if (m_backgroundTask.is_done())
            {
                logger->info("Background request task completed successfully");
                auto data = m_backgroundTask.get();
                logger->debug("Extracted {} bytes", data.size());

                m_renderer->createTexture("background", data);

                m_backgroundTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing background request: {}", e.what());
        }
    }
}
