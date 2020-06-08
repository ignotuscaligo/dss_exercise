#pragma once

#include "ui/Item.h"

#include <string>

namespace render { class Renderer; }

namespace ui
{

class ImageItem : public Item
{
public:
    void        imageName(const std::string& imageName);
    std::string imageName() const;

    void matchImageSize(bool matchImageSize);
    bool matchImageSize() const;

    bool valid(std::shared_ptr<render::Renderer> renderer) const;
    void draw(std::shared_ptr<render::Renderer> renderer) override;

private:
    std::string m_imageName{};
    bool        m_matchImageSize{false};
};

}
