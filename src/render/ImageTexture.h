#pragma once

#include "render/Texture.h"

#include <vector>

namespace render
{

class Renderer;

class ImageTexture : public Texture
{
public:
    ImageTexture(Renderer* renderer, std::vector<unsigned char>& bytes);

};

}
