#pragma once

#include "ui/Item.h"

#include <string>

namespace ui
{

class ImageItem : public Item
{
public:
    void        imageName(std::string imageName);
    std::string imageName() const;

private:
    std::string m_imageName{};
};

}
