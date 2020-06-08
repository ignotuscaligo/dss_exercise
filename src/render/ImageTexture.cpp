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
        float pixelScale = renderer->pixelScale();

        m_width = static_cast<int>(image->w / pixelScale);
        m_height = static_cast<int>(image->h / pixelScale);

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
