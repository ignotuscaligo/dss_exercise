#pragma once

namespace ui
{

struct Vector2
{
    float x;
    float y;
};

}

ui::Vector2 operator+(ui::Vector2 a, ui::Vector2 b);
ui::Vector2 operator*(ui::Vector2 a, ui::Vector2 b);
ui::Vector2 operator-(ui::Vector2 a);
