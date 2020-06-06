#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <SDL2/SDL.h>
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

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger->error("SDL could not initialize: {}", SDL_GetError());
    }
    else
    {
        m_window = SDL_CreateWindow("DSS Exercise",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  1280, 720,
                                  SDL_WINDOW_SHOWN);

        if (m_window == nullptr)
        {
            logger->error("Failed to create SDL window: {}", SDL_GetError());
        }
        else
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

            if (m_renderer == nullptr)
            {
                logger->error("Failed to create SDL renderer: {}", SDL_GetError());
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            }

            int imageInitFlags = IMG_INIT_JPG;
            int result = IMG_Init(imageInitFlags);

            if ((result & imageInitFlags) != imageInitFlags)
            {
                logger->error("Failed to initialize image loading: {}", IMG_GetError());
            }

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

                SDL_RenderClear(m_renderer);

                if (m_backgroundTexture != nullptr)
                {
                    SDL_RenderCopy(m_renderer, m_backgroundTexture, nullptr, nullptr);
                }

                SDL_RenderPresent(m_renderer);
            }
        }
    }

    if (m_backgroundTexture != nullptr)
    {
        SDL_DestroyTexture(m_backgroundTexture);
    }

    SDL_DestroyRenderer(m_renderer);

    SDL_DestroyWindow(m_window);

    IMG_Quit();
    SDL_Quit();
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
            logger->debug("game {0} venue.name: {1}", i, game.venueName());
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

                SDL_Surface* image = IMG_Load_RW(SDL_RWFromMem(data.data(), data.size()), 1);

                if (image == nullptr)
                {
                    logger->error("Failed to create image from provided data: {}", IMG_GetError());
                }
                else
                {
                    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                    m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, image);

                    if (m_backgroundTexture == nullptr)
                    {
                        logger->error("Failed to convert image to texture: {}", SDL_GetError());
                    }

                    SDL_FreeSurface(image);
                }

                m_backgroundTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing background request: {}", e.what());
        }
    }
}
