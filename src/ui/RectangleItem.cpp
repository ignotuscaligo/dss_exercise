#include "ui/RectangleItem.h"

#include "render/Renderer.h"

#include <algorithm>

namespace ui
{

void RectangleItem::fillColor(render::Color fillColor)
{
    m_fillColor = fillColor;
}

render::Color RectangleItem::fillColor() const
{
    return m_fillColor;
}

void RectangleItem::borderColor(render::Color borderColor)
{
    m_borderColor = borderColor;
}

render::Color RectangleItem::borderColor() const
{
    return m_borderColor;
}

void RectangleItem::borderWidth(int borderWidth)
{
    m_borderWidth = std::max(0, borderWidth);
}

int RectangleItem::borderWidth() const
{
    return m_borderWidth;
}

void RectangleItem::draw(std::shared_ptr<render::Renderer> renderer)
{
    auto rect = drawRect();

    if (m_fillColor.alpha > 0)
    {
        renderer->drawRect(rect, m_fillColor);
    }

    if (m_borderColor.alpha > 0 && m_borderWidth > 0)
    {
        renderer->drawOutline(rect, m_borderWidth, m_borderColor);
    }
}

}
