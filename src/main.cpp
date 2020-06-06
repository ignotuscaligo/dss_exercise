#include "Application.h"

#include "utility/string.h"
#include "utility/logging.h"

#include "mlb/Game.h"

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <exception>
#include <memory>

const utility::string_t base_url       = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

int main(int argc, char** argv)
{
    auto logger = utility::get_logger();

    logger->set_level(spdlog::level::debug);

    logger->info("Hello, world!");

    logger->info("Test cpprestsdk");

    auto requestJson = web::http::client::http_client(base_url)
        .request(web::http::methods::GET, web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                                                        .append_query(U("date"), query_date)
                                                                        .append_query(U("sportId"), query_sport_id)
                                                                        .to_string())
        .then([&logger](web::http::http_response response) {
            logger->debug("Received response: {}", response.status_code());

            if (response.status_code() != 200)
            {
                throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
            }

            return response.extract_json();
        })
        .then([&logger](web::json::value jsonObject) {
            auto totalGames = jsonObject[U("totalGames")].as_integer();
            auto gamesList = jsonObject[U("dates")][0][U("games")];

            logger->debug("totalGames: {}", totalGames);

            for (int i = 0; i < totalGames; i++)
            {
                auto game = mlb::Game(gamesList[i]);
                logger->debug("game {0} venue.name: {1}", i, game.venueName());
            }
        });

    try
    {
        requestJson.wait();
    }
    catch (const std::exception& e)
    {
        logger->error("Exception occurred while processing request: {}", e.what());
    }

    logger->info("Running application");

    Application app;

    app.run();

    logger->info("Goodbye!");

    return 0;
}
