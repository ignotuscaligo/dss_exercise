#pragma once

#include "render/Texture.h"

#include <memory>
#include <string>

namespace render
{

class Renderer;
class Font;

class TextTexture : public Texture
{
public:
    TextTexture(std::shared_ptr<Renderer> renderer, std::shared_ptr<Font> font, std::string text);
};

}
