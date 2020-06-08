#include "render/Renderer.h"

#include "render/Window.h"
#include "render/Texture.h"
#include "render/Color.h"
#include "render/Font.h"
#include "render/ImageTexture.h"
#include "render/TextTexture.h"

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

void Renderer::loadFont(std::string name, std::string filename)
{
    auto font = std::make_shared<Font>(filename);

    m_fonts[name] = font;
}

void Renderer::createImageTexture(const std::string& name, std::vector<unsigned char>& bytes)
{
    m_textures[name] = std::make_shared<ImageTexture>(this, bytes);
}

void Renderer::createTextTexture(const std::string& name, const std::string& fontName, const std::string& text)
{
    auto font = fetchFont(fontName);

    if (font)
    {
        m_textures[name] = std::make_shared<TextTexture>(this, font, text);
    }
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

std::shared_ptr<Font> Renderer::fetchFont(const std::string& name) const
{
    auto font = m_fonts.find(name);
    if (font != m_fonts.end())
    {
        return font->second;
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

void Renderer::drawRect(ui::Rect rect, Color color)
{
    SDL_FRect sdlRect = {
        rect.x(),
        rect.y(),
        rect.width(),
        rect.height()
    };

    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderFillRectF(m_renderer, &sdlRect);
}

void Renderer::drawOutline(ui::Rect rect, int width, Color color)
{
    float lineLeft = rect.left() + width / 2;
    float lineRight = rect.right() - ((width + 1) / 2);
    float lineTop = rect.top();
    float lineBottom = rect.bottom() - 1;

    float topOffset = (width / 2);
    float bottomOffset = -std::max(0, ((width - 1) / 2));

    // left
    thickLineRGBA(m_renderer, lineLeft, lineTop, lineLeft, lineBottom, width, color.red, color.green, color.blue, color.alpha);

    // top
    thickLineRGBA(m_renderer, lineLeft, lineTop + topOffset, lineRight, lineTop + topOffset, width, color.red, color.green, color.blue, color.alpha);

    // right
    thickLineRGBA(m_renderer, lineRight, lineTop, lineRight, lineBottom, width, color.red, color.green, color.blue, color.alpha);

    // bottom
    thickLineRGBA(m_renderer, lineLeft, lineBottom + bottomOffset, lineRight, lineBottom + bottomOffset, width, color.red, color.green, color.blue, color.alpha);
}

}
