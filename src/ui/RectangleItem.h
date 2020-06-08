#pragma once

#include "ui/Item.h"
#include "render/Color.h"

#include <memory>

namespace render { class Renderer; }

namespace ui
{

class RectangleItem : public Item
{
public:
    void  fillColor(render::Color fillColor);
    render::Color fillColor() const;

    void  borderColor(render::Color borderColor);
    render::Color borderColor() const;

    void borderWidth(int borderWidth);
    int  borderWidth() const;

    void draw(std::shared_ptr<render::Renderer> renderer) override;

private:
    render::Color m_fillColor;
    render::Color m_borderColor;
    int           m_borderWidth{0};
};

}
