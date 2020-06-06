#include "render/Context.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <exception>
#include <string>

namespace render
{

Context::Context()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    int imageInitFlags = IMG_INIT_JPG;
    int result = IMG_Init(imageInitFlags);

    if ((result & imageInitFlags) != imageInitFlags)
    {
        SDL_Quit();
        throw std::runtime_error("Failed to initialize image loading: " + std::string(IMG_GetError()));
    }
}

Context::~Context()
{
    IMG_Quit();
    SDL_Quit();
}

}
