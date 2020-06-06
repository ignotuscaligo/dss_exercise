#include "utility/logging.h"

#include <spdlog/spdlog.h>

namespace utility
{

std::vector<spdlog::sink_ptr> create_platform_sinks()
{
    return {};
}

}
