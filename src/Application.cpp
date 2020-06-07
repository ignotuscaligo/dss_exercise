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

const utility::string_t mlb_images_url   = U("http://mlb.mlb.com/mlb/images");
const utility::string_t background_image = U("devices/ballpark/1920x1080/1.jpg");

}

Application::Application()
: m_backgroundClient(mlb_images_url)
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
        return;
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

    m_gamesTask = m_stats.requestGamesForDate("2018-06-06");
    m_gamesTaskRunning = true;

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

    if (m_gamesTaskRunning)
    {
        try
        {
            if (m_gamesTask.is_done())
            {
                logger->info("Games task completed successfully");
                auto games = m_gamesTask.get();

                for (auto game : games)
                {
                    logger->debug("game headline: {}", game.headline());
                }

                m_gamesTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing games request: {}", e.what());
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
