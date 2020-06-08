#pragma once

struct SDL_Texture;

namespace render
{

class Texture
{
public:
    ~Texture();

    SDL_Texture* handle() const;
    int          width() const;
    int          height() const;

protected:
    SDL_Texture* m_texture{nullptr};
    int          m_width{0};
    int          m_height{0};
};

}
