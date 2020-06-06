#pragma once

#include <string>

class SDL_Window;

namespace render
{

class Window
{
public:
    Window(const std::string& name, int width, int height);
    ~Window();

    SDL_Window* handle() const;

private:
    SDL_Window* m_window{nullptr};
};

}
