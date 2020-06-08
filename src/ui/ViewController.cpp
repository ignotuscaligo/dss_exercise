#include "ui/ViewController.h"

namespace ui
{

ViewController::ViewController()
: m_rootItem(std::make_shared<ui::Item>())
, m_rowLayout(std::make_shared<ui::RowLayout>())
, m_background(std::make_shared<ui::ImageItem>())
{
    m_background->imageName("background");

    m_rootItem->addChild(m_background);

    m_rowLayout->position({30, 250});
    m_rowLayout->spacing(30);

    m_rootItem->addChild(m_rowLayout);
}

void ViewController::populateGames(std::vector<mlb::Game> games)
{
    m_gameItems.clear();

    for (int i = 0; i < games.size(); i++)
    {
        mlb::Game game = games[i];

        std::shared_ptr<ui::GameItem> item = std::make_shared<ui::GameItem>();

        item->size({123, 69});
        item->game(game);

        m_gameItems.push_back(item);
        m_rowLayout->addChild(item);
    }
}

void ViewController::update()
{
    for (int i = 0; i < m_gameItems.size(); i++)
    {
        auto item = m_gameItems[i];

        item->selected(i == m_selectedIndex);
    }
}

void ViewController::draw(std::shared_ptr<render::Renderer> renderer)
{
    m_rootItem->drawChildren(renderer);
}

}
