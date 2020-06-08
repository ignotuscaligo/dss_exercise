#pragma once

#include "ui/Rect.h"
#include "ui/Vector2.h"

#include <memory>
#include <vector>

namespace ui
{

class Item;

using ItemPtr = std::shared_ptr<Item>;
using ItemList = std::vector<ItemPtr>;

class Item
{
public:
    void    anchor(Vector2 anchor);
    Vector2 anchor() const;

    void    position(Vector2 position);
    Vector2 position() const;

    void    scale(Vector2 scale);
    Vector2 scale() const;

    void    size(Vector2 size);
    Vector2 size() const;

    Rect drawRect() const;

    void    parent(ItemPtr parent);
    ItemPtr parent();

    void     addChild(ItemPtr child);
    ItemList children();

protected:
    Vector2 m_anchor{0.0f, 0.0f};
    Vector2 m_position{0.0f, 0.0f};
    Vector2 m_scale{1.0f, 1.0f};
    Vector2 m_size{0.0f, 0.0f};

    ItemPtr  m_parent{nullptr};
    ItemList m_children;
};

}
