#pragma once

#include "render/Window.h"
#include "render/Renderer.h"
#include "render/Texture.h"
#include "render/Context.h"

#include "mlb/Stats.h"
#include "mlb/Game.h"

#include "rest/Tasks.h"

#include "ui/Item.h"

#include <pplx/pplxtasks.h>

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

class Application
{
public:
    Application();

    void run();

private:
    void initialize();
    void update();

    pplx::task<std::vector<mlb::Game>> m_gamesTask;
    bool                               m_gamesTaskRunning{false};

    mlb::Stats  m_stats;
    rest::Tasks m_tasks;

    std::shared_ptr<render::Context>  m_context{nullptr};
    std::shared_ptr<render::Window>   m_window{nullptr};
    std::shared_ptr<render::Renderer> m_renderer{nullptr};

    ui::ItemPtr m_rootItem;
};
