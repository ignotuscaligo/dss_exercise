#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

namespace utility
{

std::vector<spdlog::sink_ptr> create_platform_sinks();
std::shared_ptr<spdlog::logger> create_logger();
std::shared_ptr<spdlog::logger> get_logger();

}
