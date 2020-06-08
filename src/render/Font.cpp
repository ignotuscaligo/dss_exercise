#include "render/Font.h"

#include <exception>

namespace render
{

Font::Font(std::string filename)
{
    m_font = TTF_OpenFont(filename.c_str(), 16);

    if (m_font == nullptr)
    {
        throw std::runtime_error("Failed to create SDL font from file '" + filename + "': " + std::string(TTF_GetError()));
    }
}

Font::~Font()
{
    TTF_CloseFont(m_font);
}

TTF_Font* Font::handle() const
{
    return m_font;
}

}
