#include "ui/Vector2.h"

ui::Vector2 operator+(ui::Vector2 a, ui::Vector2 b)
{
    return {
        a.x + b.x,
        a.y + b.y
    };
}

ui::Vector2 operator*(ui::Vector2 a, ui::Vector2 b)
{
    return {
        a.x * b.x,
        a.y * b.y
    };
}

ui::Vector2 operator-(ui::Vector2 a)
{
    return {
        -a.x,
        -a.y
    };
}
