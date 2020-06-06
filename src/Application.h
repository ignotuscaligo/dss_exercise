#pragma once

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

#include <SDL2/SDL.h>

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

    SDL_Window*   m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
};
