#include "mlb/Stats.h"

#include "mlb/Game.h"

#include "utility/logging.h"

#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <ctime>

namespace
{

std::string query_string_from_date(std::tm* time)
{
    char buffer[11];
    std::strftime(buffer, 11, "%Y-%m-%d", time);
    return std::string(buffer);
}

}

namespace mlb
{

const utility::string_t statsapi_url   = U("http://statsapi.mlb.com");
const utility::string_t api_schedule   = U("api/v1/schedule");
const utility::string_t query_hydrate  = U("game(content(editorial(recap))),decisions");
const utility::string_t query_date     = U("2018-06-10");
const utility::string_t query_sport_id = U("1");

Stats::Stats()
: m_client(statsapi_url)
{
}

pplx::task<std::vector<Game>> Stats::requestCurrentGames()
{
    std::time_t now = std::time(nullptr);
    std::tm* date = std::localtime(&now);
    return requestGamesForDate(date);
}

pplx::task<std::vector<Game>> Stats::requestGamesForDate(std::tm* date)
{
    return requestGamesForDate(query_string_from_date(date));
}

pplx::task<std::vector<Game>> Stats::requestGamesForDate(std::string date)
{
    auto uri = web::uri_builder(api_schedule).append_query(U("hydrate"), query_hydrate)
                                             .append_query(U("date"), date)
                                             .append_query(U("sportId"), query_sport_id)
                                             .to_string();

    auto apiRequestTask = m_client.request(web::http::methods::GET, uri);

    auto jsonTask = apiRequestTask.then([this](web::http::http_response response) {
        return extractJsonFromResponse(response);
    });

    auto gameTask = jsonTask.then([this](web::json::value json) {
        return parseGamesFromJson(json);
    });

    return gameTask;
}

pplx::task<web::json::value> Stats::extractJsonFromResponse(web::http::http_response response)
{
    auto logger = utility::get_logger();

    logger->debug("Received response: {}", response.status_code());

    if (response.status_code() != 200)
    {
        throw std::runtime_error("Request failed " + std::to_string(response.status_code()));
    }

    return response.extract_json();
}

std::vector<Game> Stats::parseGamesFromJson(web::json::value json)
{
    auto logger = utility::get_logger();

    logger->debug("Processing extracted JSON");

    if (!json.has_field(U("totalGames")))
    {
        return {};
    }

    if (!json.has_field(U("dates")))
    {
        return {};
    }

    auto dates = json[U("dates")];

    if (dates.size() == 0)
    {
        return {};
    }

    auto firstDate = dates[0];

    if (!firstDate.has_field(U("games")))
    {
        return {};
    }

    auto totalGames = json[U("totalGames")].as_integer();
    auto gamesList  = firstDate[U("games")];

    if (gamesList.size() == 0)
    {
        return {};
    }

    logger->debug("totalGames: {}", totalGames);

    std::vector<Game> games;

    for (int i = 0; i < totalGames; i++)
    {
        games.emplace_back(gamesList[i]);
    }

    return games;
}

}
