#include "ui/GameItem.h"

namespace ui
{

GameItem::GameItem()
: m_background(std::make_shared<RectangleItem>())
, m_image(std::make_shared<ImageItem>())
, m_outline(std::make_shared<RectangleItem>())
{
    m_background->anchor({0.5f, 0.5f});
    m_background->fillColor({100, 100, 100, 255});

    m_image->anchor({0.5f, 0.5f});

    m_outline->anchor({0.5f, 0.5f});
    m_outline->borderColor({255, 255, 255, 255});
    m_outline->borderWidth(2);
    m_outline->enabled(m_selected);

    addChild(m_background);
    addChild(m_image);
    addChild(m_outline);
}

void GameItem::game(mlb::Game game)
{
    m_game = game;

    m_image->imageName(m_game.imageName());
}

mlb::Game GameItem::game() const
{
    return m_game;
}

void GameItem::selected(bool selected)
{
    m_selected = selected;

    m_outline->enabled(m_selected);
}

bool GameItem::selected() const
{
    return m_selected;
}

void GameItem::update(float deltaSeconds)
{
    m_background->position({
        m_size.x * 0.5f,
        m_size.y * 0.5f
    });

    m_image->position(m_background->position());
    m_outline->position(m_background->position());

    m_background->size(m_size);
    m_image->size(m_size);

    float targetScale = m_selected ? 1.25f : 1.0f;
    float currentScale = m_background->scale().x;
    float scaleDelta = targetScale - currentScale;

    if (std::abs(scaleDelta) > 0)
    {
        currentScale += scaleDelta * 10.0f * deltaSeconds;
    }

    m_background->scale({currentScale, currentScale});
    m_image->scale(m_background->scale());

    auto imageRect = m_image->drawRect();

    m_outline->size({
        imageRect.width() + 8,
        imageRect.height() + 8
    });
}

void GameItem::draw(std::shared_ptr<render::Renderer> renderer)
{
    bool imageValid = m_image->valid(renderer);

    m_background->enabled(!m_selected || !imageValid);
    m_image->enabled(imageValid);
    m_outline->enabled(m_selected && imageValid);
}

}
