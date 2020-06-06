#include "utility/logging.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace utility
{

spdlog::logger create_logger()
{
    auto loggingSinks = create_platform_sinks();
    auto stdoutSink   = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    loggingSinks.push_back(stdoutSink);

    return spdlog::logger("logger", loggingSinks.begin(), loggingSinks.end());
}

}
