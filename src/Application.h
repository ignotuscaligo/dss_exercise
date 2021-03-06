#pragma once

#include "render/Window.h"
#include "render/Renderer.h"
#include "render/Context.h"

#include "mlb/Stats.h"
#include "mlb/Game.h"

#include "rest/Tasks.h"

#include "ui/ViewController.h"

#include "input/State.h"

#include <pplx/pplxtasks.h>

#include <chrono>
#include <memory>
#include <vector>

class Application
{
public:
    Application();

    void run();

private:
    void initializeTasks();
    void checkTasks();

    pplx::task<std::vector<mlb::Game>> m_gamesTask;
    bool                               m_gamesTaskRunning{false};

    mlb::Stats  m_stats;
    rest::Tasks m_tasks;

    std::shared_ptr<render::Context>  m_context{nullptr};
    std::shared_ptr<render::Window>   m_window{nullptr};
    std::shared_ptr<render::Renderer> m_renderer{nullptr};

    ui::ViewController m_gameView;
    input::State       m_inputState;

    std::chrono::system_clock::time_point m_lastUpdate;
};
