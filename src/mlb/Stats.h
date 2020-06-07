#pragma once

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplxtasks.h>

#include <ctime>
#include <vector>

namespace mlb
{

class Game;

class Stats
{
public:
    Stats();

    pplx::task<std::vector<Game>> requestCurrentGames();
    pplx::task<std::vector<Game>> requestGamesForDate(std::tm* date);

private:
    pplx::task<web::json::value> extractJsonFromResponse(web::http::http_response response);
    std::vector<Game> parseGamesFromJson(web::json::value json);

    web::http::client::http_client m_client;
};

}
