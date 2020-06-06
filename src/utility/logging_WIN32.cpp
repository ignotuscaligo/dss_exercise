#include "utility/logging.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/msvc_sink.h>

#include <memory>

namespace utility
{

std::vector<spdlog::sink_ptr> create_platform_sinks()
{
    auto msvcSink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    return {msvcSink};
}

}
