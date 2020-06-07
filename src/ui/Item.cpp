#include "ui/Item.h"

#include <algorithm>

namespace ui
{

Item::Item(ItemPtr parent)
: m_parent(parent)
{
}

void Item::anchor(Vector2 anchor)
{
    m_anchor = {
        std::min(std::max(0.0f, anchor.x), 1.0f),
        std::min(std::max(0.0f, anchor.y), 1.0f)
    };
}

Vector2 Item::anchor() const
{
    return m_anchor;
}

void Item::position(Vector2 position)
{
    m_position = position;
}

Vector2 Item::position() const
{
    return m_position;
}

void Item::scale(Vector2 scale)
{
    m_scale = {
        std::max(0.0f, scale.x),
        std::max(0.0f, scale.y)
    };
}

Vector2 Item::scale() const
{
    return m_scale;
}

void Item::size(Vector2 size)
{
    m_size = {
        std::max(0.0f, size.x),
        std::max(0.0f, size.y)
    };
}

Vector2 Item::size() const
{
    return m_size;
}

Rect Item::drawRect() const
{
    Vector2 drawSize = m_size * m_scale;
    Vector2 anchorOffset = drawSize * -m_anchor;
    Vector2 drawPosition = m_position + anchorOffset;

    return {
        drawPosition.x,
        drawPosition.x + drawSize.x,
        drawPosition.y,
        drawPosition.y + drawSize.y
    };
}

}
