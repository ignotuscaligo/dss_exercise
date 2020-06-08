#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

class SDL_Renderer;

namespace ui { class Rect; }

namespace render
{

class Window;
class Texture;
class Color;
class Font;

class Renderer
{
public:
    Renderer(std::shared_ptr<Window> window);
    ~Renderer();

    SDL_Renderer* handle() const;

    void drawColor(int red, int green, int blue, int alpha);
    void clear();
    void present();

    void loadFont(std::string name, std::string filename);

    void createImageTexture(const std::string& name, std::vector<unsigned char>& bytes);
    std::shared_ptr<Texture> fetchTexture(const std::string& name) const;

    void fillTexture(std::shared_ptr<Texture> texture);
    void drawTexture(std::shared_ptr<Texture> texture, ui::Rect rect);

    void drawRect(ui::Rect rect, Color color);
    void drawOutline(ui::Rect rect, int width, Color color);
private:
    SDL_Renderer* m_renderer{nullptr};

    std::map<std::string, std::shared_ptr<Font>>    m_fonts;
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
};

}
