#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include "ui/Rect.h"
#include "ui/ImageItem.h"
#include "ui/RectangleItem.h"

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

    // Test item 1
    ui::ItemPtr gameItem0 = std::make_shared<ui::Item>();

    gameItem0->position({10, 10});

    std::shared_ptr<ui::RectangleItem> gameBackground0 = std::make_shared<ui::RectangleItem>();

    gameBackground0->size({248, 138});
    gameBackground0->fillColor({100, 100, 100, 255});

    std::shared_ptr<ui::ImageItem> gameImage0 = std::make_shared<ui::ImageItem>();

    gameImage0->size({248, 138});
    gameImage0->imageName("Nats, unfazed by Rays' strategy, cruise to win");

    std::shared_ptr<ui::RectangleItem> gameOutline0 = std::make_shared<ui::RectangleItem>();

    gameOutline0->position({-4, -4});
    gameOutline0->size({248 + 8, 138 + 8});
    gameOutline0->borderColor({255, 255, 255, 255});
    gameOutline0->borderWidth(2);

    gameItem0->addChild(gameBackground0);
    gameItem0->addChild(gameImage0);
    gameItem0->addChild(gameOutline0);
    m_rootItem->addChild(gameItem0);

    // Test item 2
    ui::ItemPtr gameItem1 = std::make_shared<ui::Item>();

    gameItem1->position({268, 10});

    std::shared_ptr<ui::RectangleItem> gameBackground1 = std::make_shared<ui::RectangleItem>();

    gameBackground1->size({248, 138});
    gameBackground1->fillColor({100, 100, 100, 255});

    std::shared_ptr<ui::ImageItem> gameImage1 = std::make_shared<ui::ImageItem>();

    gameImage1->size({248, 138});
    gameImage1->imageName("Colon ties Marichal with win No. 243");

    std::shared_ptr<ui::RectangleItem> gameOutline1 = std::make_shared<ui::RectangleItem>();

    gameOutline1->position({-4, -4});
    gameOutline1->size({248 + 8, 138 + 8});
    gameOutline1->borderColor({255, 255, 255, 255});
    gameOutline1->borderWidth(2);

    gameItem1->addChild(gameBackground1);
    gameItem1->addChild(gameImage1);
    gameItem1->addChild(gameOutline1);
    m_rootItem->addChild(gameItem1);
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

        m_rootItem->drawChildren(m_renderer);

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
