#pragma once

#include "render/Window.h"
#include "render/Renderer.h"
#include "render/Texture.h"
#include "render/Context.h"

#include "mlb/Stats.h"
#include "mlb/Game.h"

#include <cpprest/http_client.h>
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

    web::http::client::http_client         m_backgroundClient;
    pplx::task<std::vector<mlb::Game>>     m_gamesTask;
    pplx::task<std::vector<unsigned char>> m_backgroundTask;
    bool                                   m_gamesTaskRunning{false};
    bool                                   m_backgroundTaskRunning{false};

    mlb::Stats m_stats;

    std::shared_ptr<render::Context>  m_context{nullptr};
    std::shared_ptr<render::Window>   m_window{nullptr};
    std::shared_ptr<render::Renderer> m_renderer{nullptr};
};
