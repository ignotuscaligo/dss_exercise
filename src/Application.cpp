#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include "ui/Rect.h"
#include "ui/ImageItem.h"

#include "render/Color.h"

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <SDL2/SDL_image.h>

namespace
{

const utility::string_t background_image_url = U("http://mlb.mlb.com/mlb/images/devices/ballpark/1920x1080/1.jpg");

}

Application::Application()
: m_rootItem(std::make_shared<ui::Item>())
{
    auto logger = utility::get_logger();
    logger->info("Creating application");

    std::shared_ptr<ui::ImageItem> child0 = std::make_shared<ui::ImageItem>();
    std::shared_ptr<ui::ImageItem> child1 = std::make_shared<ui::ImageItem>();

    m_rootItem->addChild(child0);
    child0->parent(m_rootItem);

    m_rootItem->addChild(child1);
    child1->parent(m_rootItem);

    child0->position({10, 10});
    child0->size({248, 138});

    child0->imageName("Nats, unfazed by Rays' strategy, cruise to win");

    auto rect = child0->drawRect();

    child1->position({rect.right() + 10, 10});
    child1->size({248, 138});

    child1->imageName("Colon ties Marichal with win No. 243");
}

void Application::run()
{
    auto logger = utility::get_logger();

    logger->info("Running application");

    try
    {
        m_context = std::make_shared<render::Context>();
        m_window = std::make_shared<render::Window>("DSS Exercise", 1280, 720);
        m_renderer = std::make_shared<render::Renderer>(m_window);
    }
    catch (const std::runtime_error& e)
    {
        logger->error("Failed to initialize SDL objects: {}", e.what());
        return;
    }

    SDL_Event e;
    bool quit = false;

    initialize();

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
        }

        update();

        m_renderer->drawColor(0, 0, 0, 255);
        m_renderer->clear();

        auto background = m_renderer->fetchTexture("background");

        if (background)
        {
            m_renderer->fillTexture(background);
        }

        for (auto child : m_rootItem->children())
        {
            auto childRect = child->drawRect();

            m_renderer->drawRect(childRect, {135, 135, 135, 255});

            ui::Item outline;

            outline.position({childRect.x() - 4, childRect.y() - 4});
            outline.size({childRect.width() + 8, childRect.height() + 8});

            m_renderer->drawOutline(outline.drawRect(), 2, {255, 255, 255, 255});

            child->draw(m_renderer);
        }

        m_renderer->present();
    }

    m_renderer.reset();
    m_window.reset();
    m_context.reset();
}

void Application::initialize()
{
    auto logger = utility::get_logger();

    logger->info("Starting cpprestsdk task");

    m_gamesTask = m_stats.requestGamesForDate("2018-06-06");
    m_gamesTaskRunning = true;

    m_tasks.requestImageForRenderer("background", background_image_url, m_renderer);
}

void Application::update()
{
    auto logger = utility::get_logger();

    m_tasks.clearCompletedTasks();

    if (m_gamesTaskRunning)
    {
        try
        {
            if (m_gamesTask.is_done())
            {
                logger->info("Games task completed successfully");
                auto games = m_gamesTask.get();

                for (auto game : games)
                {
                    logger->debug("game headline: {}", game.headline());
                    logger->debug("game imageUrl: {}", game.imageUrl());

                    auto imageUrl = game.imageUrl();

                    if (!imageUrl.empty())
                    {
                        m_tasks.requestImageForRenderer(game.headline(), imageUrl, m_renderer);
                    }
                }

                m_gamesTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            logger->error("Exception occurred while processing games request: {}", e.what());
        }
    }
}
