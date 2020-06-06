#include "utility/logging.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <string>

namespace utility
{

const std::string logging_file_path{"log.txt"};

spdlog::logger create_logger()
{
    auto loggingSinks = create_platform_sinks();
    auto stdoutSink   = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto fileSink     = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logging_file_path, true);

    loggingSinks.push_back(stdoutSink);
    loggingSinks.push_back(fileSink);

    return spdlog::logger("logger", loggingSinks.begin(), loggingSinks.end());
}

}
