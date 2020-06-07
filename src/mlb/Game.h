#pragma once

#include <cpprest/json.h>

#include <string>

namespace mlb
{

class Game
{
public:
    Game(web::json::value object);

    std::string headline() const;
    std::string subHeadline() const;
    std::string imageUrl() const;
    int imageWidth() const;
    int imageHeight() const;

private:
    std::string m_headline{};
    std::string m_subHeadline{};
    std::string m_imageUrl{};
    int         m_imageWidth{0};
    int         m_imageHeight{0};
};

}
