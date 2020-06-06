#include "render/Renderer.h"

#include "render/Window.h"
#include "render/Texture.h"

#include <SDL2/SDL.h>

#include <exception>
#include <string>

namespace render
{

Renderer::Renderer(std::shared_ptr<Window> window)
{
    m_renderer = SDL_CreateRenderer(window->handle(), -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr)
    {
        throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* Renderer::handle() const
{
    return m_renderer;
}

void Renderer::drawColor(int red, int green, int blue, int alpha)
{
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
}

void Renderer::clear()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::fillTexture(std::shared_ptr<Texture> texture)
{
    SDL_RenderCopy(m_renderer, texture->handle(), nullptr, nullptr);
}

}
