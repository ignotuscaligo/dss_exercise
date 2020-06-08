#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

struct SDL_Renderer;

namespace ui { class Rect; }

namespace render
{

class Window;
class Texture;
struct Color;
class Font;

class Renderer
{
public:
    Renderer(std::shared_ptr<Window> window);
    ~Renderer();

    SDL_Renderer* handle() const;
    float         pixelScale() const;

    void drawColor(int red, int green, int blue, int alpha);
    void clear();
    void present();

    void loadFont(const std::string& name, const std::string& filename, int pointSize);

    void createImageTexture(const std::string& name, std::vector<unsigned char>& bytes);
    void createTextTexture(const std::string& name, const std::string& fontName, const std::string& text);
    std::shared_ptr<Texture> fetchTexture(const std::string& name) const;

    void fillTexture(std::shared_ptr<Texture> texture);
    void drawTexture(std::shared_ptr<Texture> texture, const ui::Rect& rect);

    void drawRect(const ui::Rect& rect, const Color& color);
    void drawOutline(const ui::Rect& rect, int width, const Color& color);

private:
    std::shared_ptr<Font> fetchFont(const std::string& name) const;

    SDL_Renderer* m_renderer{nullptr};
    float         m_pixelScale{1.0f};

    std::map<std::string, std::shared_ptr<Font>>    m_fonts;
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
};

}
