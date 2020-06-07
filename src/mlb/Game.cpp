#include "mlb/Game.h"

#include "utility/string.h"

namespace mlb
{

Game::Game(web::json::value object)
{
    auto content = object[U("content")];
    auto mlbRecap = content[U("editorial")][U("recap")][U("mlb")];
    auto imageCut = mlbRecap[U("photo")][U("cuts")][U("248x138")];

    m_headline    = utility::as_std_string(mlbRecap[U("headline")].as_string());
    m_subHeadline = utility::as_std_string(mlbRecap[U("subhead")].as_string());
    m_imageUrl    = utility::as_std_string(imageCut[U("src")].as_string());
    m_imageWidth  = utility::as_std_string(imageCut[U("width")].as_integer());
    m_imageHeight = utility::as_std_string(imageCut[U("height")].as_integer());
}

std::string Game::headline() const
{
    return m_headline;
}

std::string Game::subHeadline() const
{
    return m_subHeadline;
}

std::string Game::imageUrl() const
{
    return m_imageUrl;
}

int Game::imageWidth() const
{
    return m_imageWidth;
}

int Game::imageHeight() const
{
    return m_imageHeight;
}

}
