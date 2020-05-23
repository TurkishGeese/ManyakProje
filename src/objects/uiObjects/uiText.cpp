#include "uiText.hpp"

#include "manyakSDLttf.hpp"

#include "renderer.hpp"
#include "logger.hpp"
#include "environment.hpp"

UIText::UIText(std::string text, Vec2 position, SDL_Color color){
    SDL_Surface *textSurface = TTF_RenderText_Solid(Environment::sFont, text.c_str(), color);
    if (textSurface == nullptr) {
        Logger::logSdlTtfError("Could not create font surface.");
        return;
    }
    
    mPosition = position;
    mRenderSize = {(float) textSurface->w, (float) textSurface->h};
    mTexture = new Texture(textSurface, mRenderSize);
    SDL_FreeSurface(textSurface);
}

void UIText::setPosition(Vec2 newPosition){
    mPosition = newPosition;
}

Vec2 UIText::getSize(){
    return mRenderSize;
}