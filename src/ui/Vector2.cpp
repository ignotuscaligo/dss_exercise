#include "ui/Vector2.h"

ui::Vector2 operator+(const ui::Vector2& a, const ui::Vector2& b)
{
    return {
        a.x + b.x,
        a.y + b.y
    };
}

ui::Vector2 operator*(const ui::Vector2& a, const ui::Vector2& b)
{
    return {
        a.x * b.x,
        a.y * b.y
    };
}

ui::Vector2 operator-(const ui::Vector2& a)
{
    return {
        -a.x,
        -a.y
    };
}

ui::Vector2 operator*(const ui::Vector2& a, float b)
{
    return {
        a.x * b,
        a.y * b
    };
}
