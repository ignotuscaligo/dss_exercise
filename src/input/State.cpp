#include "input/State.h"

#include <SDL2/SDL.h>

namespace
{

SDL_Scancode scancode_for_key(input::Key key)
{
    switch (key)
    {
        case input::Key::LeftArrow:
            return SDL_SCANCODE_LEFT;

        case input::Key::RightArrow:
            return SDL_SCANCODE_RIGHT;

        default:
            return SDL_SCANCODE_UNKNOWN;
    }
}

}

namespace input
{

State::State()
{
    registerKey(Key::LeftArrow);
    registerKey(Key::RightArrow);
}

void State::update()
{
    const unsigned char* state = SDL_GetKeyboardState(nullptr);

    for (auto keyState : m_currentState)
    {
        Key key = keyState.first;
        SDL_Scancode scanCode = scancode_for_key(key);

        m_previousState[key] = m_currentState[key];
        m_currentState[key]  = state[scanCode] > 0;
    }
}

bool State::keyPressed(Key key)
{
    return m_currentState[key] && !m_previousState[key];
}

bool State::keyDown(Key key)
{
    return m_currentState[key];
}

bool State::keyReleased(Key key)
{
    return !m_currentState[key] && m_previousState[key];
}

void State::registerKey(Key key)
{
    m_currentState[key] = false;
    m_previousState[key] = m_currentState[key];
}

}
