#include "ui/Item.h"

#include <algorithm>

namespace ui
{

void Item::anchor(const Vector2& anchor)
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

void Item::position(const Vector2& position)
{
    m_position = position;
}

Vector2 Item::position() const
{
    return m_position;
}

void Item::scale(const Vector2& scale)
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

void Item::size(const Vector2& size)
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

void Item::enabled(bool enabled)
{
    m_enabled = enabled;
}

bool Item::enabled() const
{
    return m_enabled;
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

    if (m_parent != nullptr)
    {
        drawAnchor = drawAnchor + m_parent->drawAnchor();
    }

    return drawAnchor;
}

void Item::parent(Item* parent)
{
    m_parent = parent;
}

Item* Item::parent()
{
    return m_parent;
}

void Item::addChild(ItemPtr child)
{
    m_children.push_back(child);
    child->parent(this);
}

ItemList Item::children()
{
    return m_children;
}

void Item::updateChildren(float deltaSeconds)
{
    for (auto child : m_children)
    {
        if (child->enabled())
        {
            child->update(deltaSeconds);
            child->updateChildren(deltaSeconds);
        }
    }
}

void Item::drawChildren(std::shared_ptr<render::Renderer> renderer)
{
    for (auto child : m_children)
    {
        if (child->enabled())
        {
            child->draw(renderer);
            child->drawChildren(renderer);
        }
    }
}

}
