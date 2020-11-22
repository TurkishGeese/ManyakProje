#include "uiObject.hpp"

#include "renderer.hpp"

#include "environment.hpp"
#include "logger.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "assetManager.hpp"

/// <summary>
/// This function calculates what position the inner box has to be in order to be in the center of the outer box.
/// </summary>
/// <param name="outerBoxPosition">The position of the outer box</param>
/// <param name="outerBoxSize">The size of the outer box</param>
/// <param name="innerBoxSize">The size of the inner box</param>
/// <returns></returns>
Vec2 calculatePositionToCenter(Vec2 outerBoxPosition, Vec2 outerBoxSize, Vec2 innerBoxSize)
{
    return { outerBoxPosition.x + (outerBoxSize.x - innerBoxSize.x) / 2, outerBoxPosition.y + (outerBoxSize.y - innerBoxSize.y) / 2 };
}

Entity UI::createText(std::string text, Vec2 position, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(Environment::sFont, text.c_str(), color);
    if (textSurface == nullptr) {
        Logger::logSdlTtfError("Could not create font surface.");
        return INVALID_ENTITY;
    }

    Master* master = Master::getInstance();
    Entity entity = master->createEntity();
    TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(entity);
    TransformComponent* transformComponent = master->addComponentOfType<TransformComponent>(entity);
    master->finalizeEntity(entity);

    transformComponent->m_transform = position;
    textureComponent->mRenderSize = { (float)textSurface->w, (float)textSurface->h };
    textureComponent->mAsset = new Asset(new Texture(textSurface));
    textureComponent->mClip = -1;
    textureComponent->mActive = "default";
    SDL_FreeSurface(textSurface);
    return entity;
}

Entity UI::createButton(void (*func)(), std::string text, Vec2 position, Vec2 size)
{
    (void)func; // TODO ui input System of some sorts?
    Master* master = Master::getInstance();
    Entity entity = master->createEntity();
    TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(entity);
    TransformComponent* transformComponent = master->addComponentOfType<TransformComponent>(entity);
    master->finalizeEntity(entity);

    transformComponent->m_transform = position;
    textureComponent->mRenderSize = size;
    textureComponent->mAsset = AssetManager::getAsset("button");
    textureComponent->mClip = -1;
    textureComponent->mActive = "default";
    Entity textEntity = createText(text, { 0, 0 }, { 0, 0, 0 });

    // Center the text of the button
    TextureComponent* textTextureComponent = master->getComponentOfType<TextureComponent>(textEntity);
    TransformComponent* textTransformComponent = master->getComponentOfType<TransformComponent>(textEntity);
    textTransformComponent->m_transform = calculatePositionToCenter(position, size, textTextureComponent->mRenderSize);
    return entity;
}
