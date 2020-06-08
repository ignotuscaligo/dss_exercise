#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>

namespace render
{

class Font
{
public:
    Font(std::string filename);
    ~Font();

    TTF_Font* handle() const;

private:
    TTF_Font* m_font{nullptr};
};

}
