#pragma once

#include <cpprest/json.h>

namespace mlb
{

class Game
{
public:
    Game(web::json::value object);

    std::string venueName() const;

private:
    std::string m_venueName{};
};

}
