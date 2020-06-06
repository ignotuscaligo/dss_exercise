#include "mlb/Game.h"

#include "utility/string.h"

namespace mlb
{

Game::Game(web::json::value object)
{
    auto venue = object[U("venue")];
    m_venueName = utility::as_std_string(venue[U("name")].as_string());
}

std::string Game::venueName() const
{
    return m_venueName;
}

}
