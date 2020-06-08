#include "ui/ImageItem.h"

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

}
