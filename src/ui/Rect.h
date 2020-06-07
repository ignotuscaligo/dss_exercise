#pragma once

#include "ui/Vector2.h"

namespace ui
{

class Rect
{
public:
    Rect(Vector2 position, Vector2 size);

    float x() const;
    float y() const;

    float width() const;
    float height() const;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

private:
    Vector2 m_position;
    Vector2 m_size;
};

}
