#pragma once

#include "ui/Item.h"

#include <memory>

namespace render { class Renderer; }

namespace ui
{

class RowLayout : public Item
{
public:
    void  spacing(float spacing);
    float spacing() const;

    void draw(std::shared_ptr<render::Renderer> renderer) override;

private:
    float m_spacing{0};
};

}
