#include "render/Renderer.h"

#include "render/Window.h"
#include "render/Texture.h"

#include "ui/Rect.h"

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
    m_textures.clear();

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

std::shared_ptr<Texture> Renderer::createTexture(const std::string& name, std::vector<unsigned char>& bytes)
{
    auto texture = std::make_shared<Texture>(this, bytes);

    m_textures[name] = texture;

    return texture;
}

std::shared_ptr<Texture> Renderer::fetchTexture(const std::string& name) const
{
    auto texture = m_textures.find(name);
    if (texture != m_textures.end())
    {
        return texture->second;
    }
    else
    {
        return nullptr;
    }
}

void Renderer::fillTexture(std::shared_ptr<Texture> texture)
{
    SDL_RenderCopy(m_renderer, texture->handle(), nullptr, nullptr);
}

void Renderer::drawTexture(std::shared_ptr<Texture> texture, ui::Rect rect)
{
    SDL_FRect imageRect = {
        rect.x(),
        rect.y(),
        rect.width(),
        rect.height()
    };

    SDL_RenderCopyF(m_renderer, texture->handle(), nullptr, &imageRect);
}

}
