#include "utility/logging.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <string>

namespace utility
{

const std::string logger_name{"logger"};
const std::string logging_file_path{"log.txt"};

std::shared_ptr<spdlog::logger> create_logger()
{
    auto loggingSinks = create_platform_sinks();
    auto stdoutSink   = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto fileSink     = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logging_file_path, true);

    loggingSinks.push_back(stdoutSink);
    loggingSinks.push_back(fileSink);

    auto logger = std::make_shared<spdlog::logger>(logger_name, loggingSinks.begin(), loggingSinks.end());

    logger->set_level(spdlog::level::debug);

    return logger;
}

std::shared_ptr<spdlog::logger> get_logger()
{
    auto logger = spdlog::get(logger_name);

    if (!logger)
    {
        logger = create_logger();
    }

    return logger;
}

}
