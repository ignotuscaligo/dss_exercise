#pragma once

#include <pplx/pplxtasks.h>

#include <memory>
#include <string>
#include <vector>

namespace render { class Renderer; }

namespace rest
{

class Tasks
{
public:
    void requestImageForRenderer(const std::string& name, const std::string& url, std::weak_ptr<render::Renderer> renderer);

    void clearCompletedTasks();

private:
    std::vector<pplx::task<void>> m_tasks;
};

}
