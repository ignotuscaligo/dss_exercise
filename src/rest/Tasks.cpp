#include "rest/Tasks.h"

#include "render/Renderer.h"
#include "utility/logging.h"

#include <cpprest/http_client.h>

#include <stdexcept>
#include <exception>

namespace rest
{

void Tasks::requestImageForRenderer(std::string name, std::string url, std::weak_ptr<render::Renderer> renderer)
{
    auto logger = utility::get_logger();

    logger->debug("Requesting image named '{}' from {}", name, url);

    auto client = web::http::client::http_client(utility::conversions::to_string_t(url));
    auto getTask = client.request(web::http::methods::GET);
    auto vectorTask = getTask.then([name](web::http::http_response response) {
        auto logger = utility::get_logger();

        logger->debug("image '{}': Received response: {}", name, response.status_code());

        if (response.status_code() != 200)
        {
            throw std::runtime_error("image '{}': Request failed " + std::to_string(response.status_code()));
        }

        return response.extract_vector();
    });

    auto textureTask = vectorTask.then([renderer, this, name](std::vector<unsigned char> bytes) {
        auto logger = utility::get_logger();
        auto rendererLock = renderer.lock();

        if (rendererLock)
        {
            logger->debug("image '{}': Creating texture", name);
            rendererLock->createImageTexture(name, bytes);
        }

        logger->debug("image '{}': Task completed", name);
    });

    m_tasks.push_back(textureTask);
}

void Tasks::clearCompletedTasks()
{
    m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(), [](pplx::task<void> task) {
        return task.is_done();
    }), m_tasks.end());
}

}
