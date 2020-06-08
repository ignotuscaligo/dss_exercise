#pragma once

#include <cpprest/json.h>

#include <string>

namespace mlb
{

class Game
{
public:
    Game() = default;
    Game(web::json::value object);

    std::string headline() const;
    std::string subHeadline() const;
    std::string imageUrl() const;
    int         imageWidth() const;
    int         imageHeight() const;

    void        imageName(std::string imageName);
    std::string imageName() const;

private:
    std::string m_headline{};
    std::string m_subHeadline{};
    std::string m_imageUrl{};
    int         m_imageWidth{0};
    int         m_imageHeight{0};
    std::string m_imageName{};
};

}
