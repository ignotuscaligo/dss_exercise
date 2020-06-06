#pragma once

#include <memory>

class SDL_Renderer;

namespace render
{

class Window;
class Texture;

class Renderer
{
public:
    Renderer(std::shared_ptr<Window> window);
    ~Renderer();

    SDL_Renderer* handle() const;

    void drawColor(int red, int green, int blue, int alpha);
    void clear();
    void present();

    void fillTexture(std::shared_ptr<Texture> texture);

private:
    SDL_Renderer* m_renderer{nullptr};
};

}
