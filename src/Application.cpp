#include "Application.h"

#include "utility/logging.h"

#include <SDL2/SDL.h>

void Application::run()
{
    auto logger = utility::get_logger();

    logger->info("Test SDL");

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger->error("SDL could not initialize: {}", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("DSS Exercise",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  640, 480,
                                  SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            logger->error("Failed to create SDL window: {}", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 128, 180, 64));
            SDL_UpdateWindowSurface(window);

            SDL_Event e;
            bool quit = false;

            while (!quit)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    if (e.type == SDL_KEYDOWN)
                    {
                        quit = true;
                    }
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::update()
{
}
