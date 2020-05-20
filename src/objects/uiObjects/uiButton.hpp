#pragma once

#include "uiObject.hpp"

#include <string>

class UIButton : public UIObject {

public:
    // TODO currently x and y are the position of the top left. Check TODO.md#8
    UIButton(std::string idlePath, std::string activePath, float x, float y, float width, float height);

    void render() override;
    void update() override;
    bool isButtonClicked();

private:

    Texture* mTextureActive;
    bool isClicked = false; 
    float buttonWidth;
    float buttonHeight;
};