#include "uiText.hpp"

#include "manyakSDLttf.hpp"

#include "renderer.hpp"
#include "logger.hpp"
#include "environment.hpp"

UIText::UIText(std::string text, int x, int y, SDL_Color color){
    SDL_Surface *textSurface = TTF_RenderText_Solid(Environment::sFont, text.c_str(), color);
    if (textSurface == nullptr) {
        Logger::logSdlTtfError("Could not create font surface.");
        return;
    }
    mRenderBox = { x, y, textSurface->w, textSurface->h};
    mTexture = Renderer::textureFromSurface(textSurface);
    SDL_FreeSurface(textSurface);
}