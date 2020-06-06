#pragma once

#include "render/Window.h"
#include "render/Renderer.h"

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

    web::http::client::http_client         m_apiClient;
    web::http::client::http_client         m_backgroundClient;
    pplx::task<void>                       m_apiTask;
    pplx::task<std::vector<unsigned char>> m_backgroundTask;
    bool                                   m_apiTaskRunning{false};
    bool                                   m_backgroundTaskRunning{false};

    std::shared_ptr<render::Window>   m_window{nullptr};
    std::shared_ptr<render::Renderer> m_renderer{nullptr};

    SDL_Texture*  m_backgroundTexture{nullptr};
};
