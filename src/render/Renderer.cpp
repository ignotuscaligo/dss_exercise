#include "render/Renderer.h"

#include "render/Window.h"
#include "render/Texture.h"

#include "ui/Rect.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <algorithm>
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

    SDL_RenderSetScale(m_renderer, 2, 2);
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

void Renderer::drawRect(ui::Rect rect, int red, int green, int blue, int alpha)
{
    SDL_FRect sdlRect = {
        rect.x(),
        rect.y(),
        rect.width(),
        rect.height()
    };

    SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
    SDL_RenderFillRectF(m_renderer, &sdlRect);
}

void Renderer::drawOutline(ui::Rect rect, int width, int red, int green, int blue, int alpha)
{
    float lineLeft = rect.left() + width / 2;
    float lineRight = rect.right() - ((width + 1) / 2);
    float lineTop = rect.top();
    float lineBottom = rect.bottom() - 1;

    float topOffset = (width / 2);
    float bottomOffset = -std::max(0, ((width - 1) / 2));

    // left
    thickLineRGBA(m_renderer, lineLeft, lineTop, lineLeft, lineBottom, width, red, green, blue, alpha);

    // top
    thickLineRGBA(m_renderer, lineLeft, lineTop + topOffset, lineRight, lineTop + topOffset, width, red, green, blue, alpha);

    // right
    thickLineRGBA(m_renderer, lineRight, lineTop, lineRight, lineBottom, width, red, green, blue, alpha);

    // bottom
    thickLineRGBA(m_renderer, lineLeft, lineBottom + bottomOffset, lineRight, lineBottom + bottomOffset, width, red, green, blue, alpha);
}

}
