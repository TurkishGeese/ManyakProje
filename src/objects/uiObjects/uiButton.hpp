#pragma once

#include "uiObject.hpp"
#include "uiText.hpp"

#include <string>

class UIButton : public UIObject {

public:
    // TODO currently x and y are the position of the top left. Check TODO.md#8
    UIButton(void (*func)(), std::string text, Vec2 position, Vec2 size);

    virtual ~UIButton() override;
    void render() override;
    void update() override;


private:

    void (*mFunction)();
    bool isButtonClicked();
    Vec2 calculateTextPosition();
    UIText* mText;
    Vec2 textPosition;
    std::string idlePath = "buttonIdle.png";
    std::string activePath = "buttonActive.png";
    Texture* mTextureActive;
    bool isClicked = false; 
};