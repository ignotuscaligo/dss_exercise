#include "TextItem.h"

#include "render/Renderer.h"
#include "render/Texture.h"

#include "utility/logging.h"

#include <sstream>
#include <algorithm>

namespace ui
{

void TextItem::fontName(std::string fontName)
{
    m_fontName = fontName;
}

std::string TextItem::fontName() const
{
    return m_fontName;
}

void TextItem::text(std::string text)
{
    auto logger = utility::get_logger();

    m_text = text;

    m_lines.clear();

    if (m_maxCharacterWidth < 1)
    {
        m_lines.push_back(m_text);
    }
    else
    {
        std::stringstream stream(m_text);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(stream, token, ' '))
        {
            tokens.push_back(token);
        }

        std::string currentLine = "";

        for (int i = 0; i < tokens.size(); i++)
        {
            if (!currentLine.empty())
            {
                currentLine += " ";
            }

            currentLine += tokens[i];

            if (currentLine.size() > m_maxCharacterWidth)
            {
                m_lines.push_back(currentLine);
                currentLine = "";
            }
        }

        if (!currentLine.empty())
        {
            m_lines.push_back(currentLine);
        }

        logger->debug("m_text: \"{}\"", m_text);
        logger->debug("m_lines.size(): {}", m_lines.size());

        logger->debug("m_lines:");

        for (auto line : m_lines)
        {
            logger->debug("    {}", line);
        }
    }
}

std::string TextItem::text() const
{
    return m_text;
}

void TextItem::maxCharacterWidth(int maxCharacterWidth)
{
    m_maxCharacterWidth = maxCharacterWidth;
}

int TextItem::maxCharacterWidth() const
{
    return m_maxCharacterWidth;
}

void TextItem::draw(std::shared_ptr<render::Renderer> renderer)
{
    auto logger = utility::get_logger();

    if (m_lines.empty() || m_fontName.empty() || m_text.empty())
    {
        return;
    }
    else
    {
        float totalHeight = 0;
        float maxWidth = 0;

        std::vector<std::shared_ptr<render::Texture>> textures;

        for (auto line : m_lines)
        {
            auto imageName = m_fontName + "|" + line;
            auto image = renderer->fetchTexture(imageName);

            if (!image)
            {
                renderer->createTextTexture(imageName, m_fontName, line);
                image = renderer->fetchTexture(imageName);
            }

            textures.push_back(image);

            totalHeight += image->height();
            maxWidth = std::max(maxWidth, static_cast<float>(image->width()));
        }

        size({maxWidth, totalHeight});

        std::vector<Rect> rects;

        Rect parentRect = drawRect();

        float runningPosition = 0;

        for (auto texture : textures)
        {
            float widthDifference = maxWidth - texture->width();

            Rect localRect{
                {widthDifference / 2.0f,
                runningPosition},
                {static_cast<float>(texture->width()),
                static_cast<float>(texture->height())}
            };

            Rect drawRect{
                {parentRect.x() + localRect.x(),
                parentRect.y() + localRect.y()},
                {localRect.width(),
                localRect.height()}
            };

            rects.push_back(drawRect);
            runningPosition += texture->height();
        }

        for (int i = 0; i < textures.size(); i++)
        {
            renderer->drawTexture(textures[i], rects[i]);
        }
    }
}

}
