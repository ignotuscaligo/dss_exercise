#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <SDL2/SDL.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/msvc_sink.h>

#include <exception>
#include <memory>
#include <locale>
#include <codecvt>

const utility::string_t base_url       = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

std::string as_std_string(std::wstring input)
{
    using convert_type = std::codecvt_utf8<wchar_t>;

    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.to_bytes(input);
}

std::string as_std_string(std::string input)
{
    return input;
}

int main(int argc, char** argv)
{
    auto msvcSink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto logger = spdlog::logger("logger", {msvcSink, stdoutSink});

    logger.set_level(spdlog::level::debug);

    logger.info("Hello, world!");

    logger.info("Test cpprestsdk");

    auto requestJson = web::http::client::http_client(base_url)
        .request(web::http::methods::GET, web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                                                        .append_query(U("date"), query_date)
                                                                        .append_query(U("sportId"), query_sport_id)
                                                                        .to_string())
        .then([&logger](web::http::http_response response) {
            logger.debug("Received response: {}", response.status_code());

            if (response.status_code() != 200)
            {
                throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
            }

            return response.extract_json();
        })
        .then([&logger](web::json::value jsonObject) {
            auto totalGames = jsonObject[U("totalGames")].as_integer();
            auto gamesList = jsonObject[U("dates")][0][U("games")];

            logger.debug("totalGames: {}", totalGames);

            for (int i = 0; i < totalGames; i++)
            {
                auto game = gamesList[i];
                auto venue = game[U("venue")];

                auto venueName = as_std_string(venue[U("name")].as_string());

                logger.debug("game {0} venue.name: {1}", i, venueName);
            }
        });

    try
    {
        requestJson.wait();
    }
    catch (const std::exception& e)
    {
        logger.error("Exception occurred while processing request: {}", e.what());
    }

    logger.info("Test SDL");

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger.error("SDL could not initialize: {}", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("DSS Exercise",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  640, 480,
                                  SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            logger.error("Failed to create SDL window: {}", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 128, 180, 64));
            SDL_UpdateWindowSurface(window);

            SDL_Event e;
            bool quit = false;

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
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    logger.info("Goodbye!");

    return 0;
}
