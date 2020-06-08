#pragma once

#include "ui/Item.h"
#include "ui/ImageItem.h"
#include "ui/RectangleItem.h"
#include "mlb/Game.h"

namespace render { class Renderer; }

namespace ui
{

class GameItem : public Item
{
public:
    GameItem();

    void      game(mlb::Game game);
    mlb::Game game() const;

    void selected(bool selected);
    bool selected() const;

    void draw(std::shared_ptr<render::Renderer> renderer) override;

private:
    mlb::Game m_game;
    bool      m_selected{false};

    std::shared_ptr<RectangleItem> m_background;
    std::shared_ptr<ImageItem>     m_image;
    std::shared_ptr<RectangleItem> m_outline;
};

}
