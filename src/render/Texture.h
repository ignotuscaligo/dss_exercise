#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace render
{

class Renderer;

class Texture
{
public:
    Texture(std::shared_ptr<Renderer> renderer, std::vector<unsigned char>& bytes);
    ~Texture();

    SDL_Texture* handle() const;

private:
    SDL_Texture* m_texture{nullptr};
};

}
