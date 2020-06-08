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
    TextTexture(Renderer* renderer, std::shared_ptr<Font> font, const std::string& text);
};

}
