#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>

namespace render
{

class Font
{
public:
    Font(const std::string& filename, int pixelSize);
    ~Font();

    TTF_Font* handle() const;

private:
    TTF_Font* m_font{nullptr};
};

}
