#include "render/ImageTexture.h"

#include "render/Renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <exception>
#include <string>

namespace render
{

ImageTexture::ImageTexture(Renderer* renderer, std::vector<unsigned char>& bytes)
{
    SDL_Surface* image = IMG_Load_RW(SDL_RWFromMem(bytes.data(), bytes.size()), 1);

    if (image == nullptr)
    {
        throw std::runtime_error("Failed to create image from provided bytes: " + std::string(IMG_GetError()));
    }
    else
    {
        m_width = image->w;
        m_height = image->h;

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        m_texture = SDL_CreateTextureFromSurface(renderer->handle(), image);

        SDL_FreeSurface(image);

        if (m_texture == nullptr)
        {
            throw std::runtime_error("Failed to convert image to texture: " + std::string(SDL_GetError()));
        }
    }
}

}
