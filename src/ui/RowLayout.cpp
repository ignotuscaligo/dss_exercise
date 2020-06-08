#include "ui/RowLayout.h"

#include "render/Renderer.h"

namespace ui
{

void RowLayout::spacing(float spacing)
{
    m_spacing = spacing;
}

float RowLayout::spacing() const
{
    return m_spacing;
}

void RowLayout::draw(std::shared_ptr<render::Renderer>)
{
    int childCount = m_children.size();
    float childrenWidth = 0;
    float maxHeight = 0;

    for (auto child : m_children)
    {
        auto size = child->size();

        childrenWidth += size.x;
        maxHeight = std::max(maxHeight, size.y);
    }

    float totalWidth = childrenWidth + ((childCount - 1) * m_spacing);

    size({totalWidth, maxHeight});

    float runningPosition = -m_anchor.x * m_size.x;
    float childY = -m_anchor.y * m_size.y;

    for (int i = 0; i < childCount; i++)
    {
        auto child = m_children[i];

        child->position({runningPosition, childY});

        runningPosition += child->size().x + m_spacing;
    }
}

}
