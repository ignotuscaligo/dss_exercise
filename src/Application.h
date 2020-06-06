#pragma once

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

class Application
{
public:
    Application();

    void run();

private:
    void initialize();
    void update();

    web::http::client::http_client m_client;
    pplx::task<void>               m_task;
    bool                           m_taskRunning{false};
};
