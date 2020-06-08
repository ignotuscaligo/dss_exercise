#include "ui/Rect.h"

namespace ui
{

Rect::Rect(const Vector2& position, const Vector2& size)
: m_position(position)
, m_size(size)
{
}

float Rect::x() const
{
    return m_position.x;
}

float Rect::y() const
{
    return m_position.y;
}

float Rect::width() const
{
    return m_size.x;
}

float Rect::height() const
{
    return m_size.y;
}

float Rect::left() const
{
    return x();
}

float Rect::right() const
{
    return m_position.x + m_size.x;
}

float Rect::top() const
{
    return y();
}

float Rect::bottom() const
{
    return m_position.y + m_size.y;
}

}
