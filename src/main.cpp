#include "Application.h"

#include "utility/logging.h"

#include <SDL2/SDL.h>

extern "C" int main(int argc, char** argv)
{
    auto logger = utility::get_logger();

    logger->info("Hello!");

    Application app;

    app.run();

    logger->info("Goodbye!");

    return 0;
}
