#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

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

    std::shared_ptr<Texture> createTexture(const std::string& name, std::vector<unsigned char>& bytes);
    std::shared_ptr<Texture> fetchTexture(const std::string& name) const;
    void fillTexture(std::shared_ptr<Texture> texture);

private:
    SDL_Renderer* m_renderer{nullptr};

    std::map<std::string, std::shared_ptr<Texture>> m_textures;
};

}
