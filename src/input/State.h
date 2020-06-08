#pragma once

#include <map>
#include <vector>
#include <set>

namespace input
{

enum class Key
{
    LeftArrow,
    RightArrow
};

class State
{
public:
    State();

    void update();

    bool keyPressed(Key keyIndex);
    bool keyDown(Key keyIndex);
    bool keyReleased(Key keyIndex);

private:
    void registerKey(Key key);

    std::map<Key, bool> m_currentState;
    std::map<Key, bool> m_previousState;
};

}
