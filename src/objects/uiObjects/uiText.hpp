#pragma once

#include "uiObject.hpp"

#include <string>

class UIText : public UIObject {

public:
    // TODO currently x and y are the position of the top left. Check TODO.md#8
    // Add size parameter later (Vec2 size)
    UIText(std::string text, Vec2 position, SDL_Color color);
    void setPosition(Vec2 newPosition);
    Vec2 getSize();
};