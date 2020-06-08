#include "Application.h"

#include "utility/logging.h"
#include "utility/string.h"

#include "mlb/Game.h"

#include "ui/Rect.h"
#include "ui/ImageItem.h"
#include "ui/RectangleItem.h"
#include "ui/RowLayout.h"
#include "ui/GameItem.h"

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

    std::shared_ptr<ui::RowLayout> row = std::make_shared<ui::RowLayout>();

    row->position({9, 250});
    row->spacing(30);

    m_rootItem->addChild(row);
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

                auto rowLayout = m_rootItem->children()[0];

                int i = 0;

                for (auto game : games)
                {
                    logger->debug("game headline: {}", game.headline());
                    logger->debug("game imageUrl: {}", game.imageUrl());

                    std::shared_ptr<ui::GameItem> item = std::make_shared<ui::GameItem>();

                    item->size({123, 69});
                    item->game(game);

                    rowLayout->addChild(item);

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
