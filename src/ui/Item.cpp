#include "ui/Item.h"

#include <algorithm>

namespace ui
{

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
    Vector2 drawPosition = drawAnchor() + anchorOffset;

    return {drawPosition, drawSize};
}

Vector2 Item::drawAnchor() const
{
    Vector2 drawAnchor = m_position;

    if (m_parent)
    {
        drawAnchor = drawAnchor + m_parent->drawAnchor();
    }

    return drawAnchor;
}

void Item::parent(ItemPtr parent)
{
    m_parent = parent;
}

ItemPtr Item::parent()
{
    return m_parent;
}

void Item::addChild(ItemPtr child)
{
    m_children.push_back(child);
}

ItemList Item::children()
{
    return m_children;
}

}
