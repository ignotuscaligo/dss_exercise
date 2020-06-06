#pragma once

#include <spdlog/spdlog.h>

#include <vector>

namespace utility
{

std::vector<spdlog::sink_ptr> create_platform_sinks();
spdlog::logger create_logger();

}
