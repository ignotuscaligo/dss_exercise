#pragma once

namespace ui
{

struct Vector2
{
    float x;
    float y;
};

}

ui::Vector2 operator+(const ui::Vector2& a, const ui::Vector2& b);
ui::Vector2 operator*(const ui::Vector2& a, const ui::Vector2& b);
ui::Vector2 operator-(const ui::Vector2& a);

ui::Vector2 operator*(const ui::Vector2& a, float b);
