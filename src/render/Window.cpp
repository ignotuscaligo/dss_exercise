#include "render/Window.h"

#include <SDL2/SDL.h>

#include <exception>

namespace render
{

Window::Window(const std::string& name, int width, int height)
{
    m_window = SDL_CreateWindow(name.c_str(),
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                width, height,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    if (m_window == nullptr)
    {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

SDL_Window* Window::handle() const
{
    return m_window;
}

}
