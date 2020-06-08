#include "render/Texture.h"

#include "render/Renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <exception>
#include <string>

namespace render
{

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

SDL_Texture* Texture::handle() const
{
    return m_texture;
}

}
