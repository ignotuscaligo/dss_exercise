#pragma once

#include "ui/Item.h"

#include <string>
#include <vector>

namespace ui
{

class TextItem : public Item
{
public:
    void        fontName(std::string fontName);
    std::string fontName() const;

    void        text(std::string text);
    std::string text() const;

    void maxCharacterWidth(int maxCharacterWidth);
    int  maxCharacterWidth() const;

    void draw(std::shared_ptr<render::Renderer> renderer) override;

private:
    std::string m_fontName;
    std::string m_text;
    int         m_maxCharacterWidth{0};

    std::vector<std::string> m_lines;
    std::vector<std::string> m_lineImages;
};

}
