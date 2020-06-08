#pragma once

class SDL_Texture;

namespace render
{

class Texture
{
public:
    ~Texture();

    SDL_Texture* handle() const;

protected:
    SDL_Texture* m_texture{nullptr};
};

}
