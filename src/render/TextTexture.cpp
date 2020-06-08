#include "render/TextTexture.h"

#include "render/Font.h"
#include "render/Renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace render
{

TextTexture::TextTexture(Renderer* renderer, std::shared_ptr<Font> font, std::string text)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font->handle(), text.c_str(), {255, 255, 255, 255});

    if (textSurface == nullptr)
    {
        throw std::runtime_error("Failed to create texture for text '" + text + "': " + std::string(TTF_GetError()));
    }
    else
    {
        float pixelScale = renderer->pixelScale();

        m_width = static_cast<int>(textSurface->w / pixelScale);
        m_height = static_cast<int>(textSurface->h / pixelScale);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        m_texture = SDL_CreateTextureFromSurface(renderer->handle(), textSurface);

        SDL_FreeSurface(textSurface);

        if (m_texture == nullptr)
        {
            throw std::runtime_error("Failed to convert text surface to texture: " + std::string(SDL_GetError()));
        }
    }
}

}
