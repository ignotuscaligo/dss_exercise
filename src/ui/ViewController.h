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

    void selectedIndex(int selectedIndex);
    int  selectedIndex() const;

    void selectNext();
    void selectPrevious();

    void populateGames(std::vector<mlb::Game> games);
    void update(float deltaSeconds);
    void draw(std::shared_ptr<render::Renderer> renderer);

private:
    ItemPtr                    m_rootItem;
    std::shared_ptr<RowLayout> m_rowLayout;
    std::shared_ptr<ImageItem> m_background;

    std::vector<std::shared_ptr<GameItem>> m_gameItems;

    int m_selectedIndex{0};
};

}
