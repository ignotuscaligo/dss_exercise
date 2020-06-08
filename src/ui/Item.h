#pragma once

#include "ui/Rect.h"
#include "ui/Vector2.h"

#include <memory>
#include <vector>

namespace render { class Renderer; }

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

    Rect    drawRect() const;
    Vector2 drawAnchor() const;

    void     addChild(ItemPtr child);
    ItemList children();

    void drawChildren(std::shared_ptr<render::Renderer> renderer);
    virtual void draw(std::shared_ptr<render::Renderer> renderer) {};

protected:
    void  parent(Item* parent);
    Item* parent();

    Vector2 m_anchor{0.0f, 0.0f};
    Vector2 m_position{0.0f, 0.0f};
    Vector2 m_scale{1.0f, 1.0f};
    Vector2 m_size{0.0f, 0.0f};

    Item*    m_parent{nullptr};
    ItemList m_children;
};

}
