#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <SDL2/SDL.h>

namespace
{

const utility::string_t base_url       = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

}

Application::Application()
: m_client(base_url)
{
    auto logger = utility::get_logger();
    logger->info("Creating application");
}

void Application::run()
{
    auto logger = utility::get_logger();

    logger->info("Running application");

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger->error("SDL could not initialize: {}", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("DSS Exercise",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  640, 480,
                                  SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            logger->error("Failed to create SDL window: {}", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 128, 180, 64));
            SDL_UpdateWindowSurface(window);

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
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::initialize()
{
    auto logger = utility::get_logger();

    logger->info("Starting cpprestsdk task");

    auto requestTask = m_client.request(web::http::methods::GET, web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                                                                               .append_query(U("date"), query_date)
                                                                                               .append_query(U("sportId"), query_sport_id)
                                                                                               .to_string());

    auto jsonTask = requestTask.then([](web::http::http_response response) {
        auto logger = utility::get_logger();

        logger->debug("Received response: {}", response.status_code());

        if (response.status_code() != 200)
        {
            throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
        }

        return response.extract_json();
    });

    m_task = jsonTask.then([](web::json::value jsonObject) {
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

    m_taskRunning = true;
}

void Application::update()
{
    auto logger = utility::get_logger();

    if (m_taskRunning)
    {
        try
        {
            if (m_task.is_done())
            {
                logger->info("Request task completed successfully");
                m_taskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing request: {}", e.what());
        }
    }
}
