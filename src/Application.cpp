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
#include "render/Font.h"

#include <SDL2/SDL_image.h>

namespace
{

const std::string background_image_url = "http://mlb.mlb.com/mlb/images/devices/ballpark/1920x1080/1.jpg";

}

Application::Application()
{
    auto logger = utility::get_logger();
    logger->info("Creating application");
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

        m_renderer->loadFont("label_headline", "Roboto-Medium.ttf", 15);
        m_renderer->loadFont("label_subheadline", "Roboto-Medium.ttf", 11);
    }
    catch (const std::runtime_error& e)
    {
        logger->error("Failed to initialize SDL objects: {}", e.what());
        return;
    }

    SDL_Event e;
    bool quit = false;

    initializeTasks();

    m_lastUpdate = std::chrono::system_clock::now();

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        checkTasks();

        auto currentTime = std::chrono::system_clock::now();
        auto deltaTime = currentTime - m_lastUpdate;
        m_lastUpdate = currentTime;

        float deltaSeconds = std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count();

        m_inputState.update();

        if (m_inputState.keyPressed(input::Key::LeftArrow))
        {
            m_gameView.selectPrevious();
        }

        if (m_inputState.keyPressed(input::Key::RightArrow))
        {
            m_gameView.selectNext();
        }

        m_gameView.update(deltaSeconds);

        m_renderer->drawColor(0, 0, 0, 255);
        m_renderer->clear();

        m_gameView.draw(m_renderer);

        m_renderer->present();
    }

    m_renderer.reset();
    m_window.reset();
    m_context.reset();
}

void Application::initializeTasks()
{
    auto logger = utility::get_logger();

    logger->info("Requesting games list from API");

    // Get list of games for today
    // Often missing images and descriptive text
    //m_gamesTask = m_stats.requestCurrentGames();

    // Get list of games for specific date
    m_gamesTask = m_stats.requestGamesForDate("2018-06-06");
    // m_gamesTask = m_stats.requestGamesForDate("2019-06-06");

    m_gamesTaskRunning = true;

    m_tasks.requestImageForRenderer("background", background_image_url, m_renderer);
}

void Application::checkTasks()
{
    auto logger = utility::get_logger();

    m_tasks.clearCompletedTasks();

    if (m_gamesTaskRunning)
    {
        try
        {
            if (m_gamesTask.is_done())
            {
                auto games = m_gamesTask.get();

                for (int i = 0; i < games.size(); i++)
                {
                    auto& game = games[i];

                    logger->debug("game headline: {}", game.headline());
                    logger->debug("game imageUrl: {}", game.imageUrl());

                    auto imageUrl  = game.imageUrl();
                    auto imageName = "game" + std::to_string(i);

                    if (!imageUrl.empty())
                    {
                        m_tasks.requestImageForRenderer(imageName, imageUrl, m_renderer);
                        game.imageName(imageName);
                    }
                }

                m_gameView.populateGames(games);

                logger->debug("Games list received successfully");
                m_gamesTaskRunning = false;
            }
        }
        catch (const std::exception& e)
        {
            m_gamesTaskRunning = false;
            logger->error("Exception occurred while processing games request: {}", e.what());
        }
    }
}
