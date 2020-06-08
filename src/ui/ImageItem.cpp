#include "ui/ImageItem.h"

#include "render/Renderer.h"
#include "render/Texture.h"

namespace ui
{

void ImageItem::imageName(const std::string& imageName)
{
    m_imageName = imageName;
}

std::string ImageItem::imageName() const
{
    return m_imageName;
}

void ImageItem::matchImageSize(bool matchImageSize)
{
    m_matchImageSize = matchImageSize;
}

bool ImageItem::matchImageSize() const
{
    return m_matchImageSize;
}

bool ImageItem::valid(std::shared_ptr<render::Renderer> renderer) const
{
    return renderer->fetchTexture(m_imageName) != nullptr;
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
            if (m_matchImageSize)
            {
                size({
                    static_cast<float>(image->width()),
                    static_cast<float>(image->height())
                });
            }

            renderer->drawTexture(image, drawRect());
        }
    }
}

}
