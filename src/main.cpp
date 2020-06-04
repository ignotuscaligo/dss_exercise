#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <exception>
#include <iostream>

const utility::string_t base_url       = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

int main(int argc, char** argv)
{
    std::cout << "Hello, world!\n";

    auto requestJson = web::http::client::http_client(base_url)
        .request(web::http::methods::GET, web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                                                        .append_query(U("date"), query_date)
                                                                        .append_query(U("sportId"), query_sport_id)
                                                                        .to_string())
        .then([](web::http::http_response response) {
            std::cout << "Received response: " << response.status_code() << "\n";
            if (response.status_code() != 200)
            {
                throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
            }

            return response.extract_json();
        })
        .then([](web::json::value jsonObject) {
            auto totalGames = jsonObject[U("totalGames")].as_integer();
            auto gamesList = jsonObject[U("dates")][0][U("games")];

            std::cout << "totalGames: " << totalGames << "\n";

            for (int i = 0; i < totalGames; i++)
            {
                auto game = gamesList[i];
                auto venue = game[U("venue")];

                std::cout << "game " << i << " venue.name: " << venue[U("name")].as_string() << "\n";
            }
        });

    try
    {
        requestJson.wait();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception occurred while processing request: " << e.what() << "\n";
    }

    std::cout << "Goodbye!\n";

    return 0;
}
