#include "ui/ImageItem.h"

#include "render/Renderer.h"

namespace ui
{

void ImageItem::imageName(std::string imageName)
{
    m_imageName = imageName;
}

std::string ImageItem::imageName() const
{
    return m_imageName;
}

void ImageItem::draw(std::shared_ptr<render::Renderer> renderer)
{
    if (m_imageName.empty())
    {
        return;
    }
    else
    {
        auto image = renderer->fetchTexture(m_imageName);

        if (image)
        {
            renderer->drawTexture(image, drawRect());
        }
    }
}

}
