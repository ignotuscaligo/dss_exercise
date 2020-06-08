#include "mlb/Game.h"

#include "utility/string.h"

namespace mlb
{

Game::Game(web::json::value object)
{
    auto content = object[U("content")];

    if (content.has_field(U("editorial")))
    {
        auto editorial = content[U("editorial")];

        if (editorial.has_field(U("recap")))
        {
            auto recap = editorial[U("recap")];

            if (recap.has_field(U("mlb")))
            {
                auto mlbRecap = recap[U("mlb")];

                m_headline    = utility::as_std_string(mlbRecap[U("headline")].as_string());
                m_subHeadline = utility::as_std_string(mlbRecap[U("subhead")].as_string());

                auto imageCut = mlbRecap[U("photo")][U("cuts")][U("496x279")];

                m_imageUrl    = utility::as_std_string(imageCut[U("src")].as_string());
                m_imageWidth  = imageCut[U("width")].as_integer();
                m_imageHeight = imageCut[U("height")].as_integer();
            }
        }
    }

    if (m_headline.empty())
    {
        auto homeTeam = utility::as_std_string(object[U("teams")][U("home")][U("team")][U("name")].as_string());
        auto awayTeam = utility::as_std_string(object[U("teams")][U("away")][U("team")][U("name")].as_string());

        m_headline = homeTeam + " vs. " + awayTeam;
    }
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
