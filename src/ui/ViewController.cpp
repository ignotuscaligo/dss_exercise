#include "ui/ViewController.h"

#include <algorithm>
#include <cmath>

namespace ui
{

ViewController::ViewController()
: m_rootItem(std::make_shared<ui::Item>())
, m_rowLayout(std::make_shared<ui::RowLayout>())
, m_background(std::make_shared<ui::ImageItem>())
{
    m_background->imageName("background");
    m_background->size({1280, 720});

    m_rootItem->addChild(m_background);

    m_rowLayout->position({30, 250});
    m_rowLayout->spacing(30);

    m_rootItem->addChild(m_rowLayout);

    auto testImage = std::make_shared<ImageItem>();

    testImage->size({100, 20});
    testImage->position({50, 500});
    testImage->imageName("testLabel");

    m_rootItem->addChild(testImage);
}

void ViewController::selectedIndex(int selectedIndex)
{
    m_selectedIndex = std::min(std::max(0, selectedIndex), static_cast<int>(m_gameItems.size()) - 1);
}

int ViewController::selectedIndex() const
{
    return m_selectedIndex;
}

void ViewController::selectNext()
{
    selectedIndex(m_selectedIndex + 1);
}

void ViewController::selectPrevious()
{
    selectedIndex(m_selectedIndex - 1);
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

void ViewController::update(float deltaSeconds)
{
    for (int i = 0; i < m_gameItems.size(); i++)
    {
        auto item = m_gameItems[i];

        item->selected(i == m_selectedIndex);
    }

    float drawableArea = m_background->size().x - 60;
    float rowWidth = m_rowLayout->size().x;
    float difference = rowWidth - drawableArea;
    float rowPosition = 30;

    if (difference > 0 && m_gameItems.size() > 1)
    {
        float offset = m_selectedIndex * (difference / static_cast<float>(m_gameItems.size() - 1));
        rowPosition = 30 - offset;
    }

    float currentPosition = m_rowLayout->position().x;
    float positionDelta = rowPosition - currentPosition;

    if (std::abs(positionDelta) > 0)
    {
        currentPosition += positionDelta * 5 * deltaSeconds;
    }

    m_rowLayout->position({currentPosition, 250});

    m_rootItem->updateChildren(deltaSeconds);
}

void ViewController::draw(std::shared_ptr<render::Renderer> renderer)
{
    m_rootItem->drawChildren(renderer);
}

}
