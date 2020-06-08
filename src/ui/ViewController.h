#pragma once

#include "ui/GameItem.h"
#include "ui/Item.h"
#include "ui/ImageItem.h"
#include "ui/RowLayout.h"

#include <memory>

namespace render { class Renderer; }

namespace ui
{

class ViewController
{
public:
    ViewController();

    void selectedIndex(int index);
    int  selectedIndex() const;

    void populateGames(std::vector<mlb::Game> games);
    void update();
    void draw(std::shared_ptr<render::Renderer> renderer);

private:
    ItemPtr                    m_rootItem;
    std::shared_ptr<RowLayout> m_rowLayout;
    std::shared_ptr<ImageItem> m_background;

    std::vector<std::shared_ptr<GameItem>> m_gameItems;

    int m_selectedIndex{0};
};

}
