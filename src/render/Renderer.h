#pragma once

#include "render/Window.h"

#include <SDL2/SDL.h>

#include <memory>

namespace render
{

class Renderer
{
public:
    Renderer(std::shared_ptr<Window> window);
    ~Renderer();

    SDL_Renderer* handle() const;

    void drawColor(int red, int green, int blue, int alpha);
    void clear();
    void copy(SDL_Texture* texture);
    void present();

private:
    SDL_Renderer* m_renderer{nullptr};
};

}
