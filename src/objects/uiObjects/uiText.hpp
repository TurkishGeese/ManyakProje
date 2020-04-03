#pragma once

#include "uiObject.hpp"

#include <string>

class UIText : public UIObject {

public:
    // TODO currently x and y are the position of the top left. Check TODO.md#8
    UIText(std::string text, int x, int y, SDL_Color color);
};