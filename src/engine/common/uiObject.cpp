#include "uiObject.hpp"

#include "renderer.hpp"

#include "environment.hpp"
#include "logger.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "uiInputComponent.hpp"
#include "assetManager.hpp"
#include "inputManager.hpp"

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

bool isPointInsideBox(Vec2 boxPosition, Vec2 boxSize, Vec2 position)
{
    if ((position.x >= boxPosition.x && position.x <= boxPosition.x + boxSize.x) &&
        (position.y >= boxPosition.y && position.y <= boxPosition.y + boxSize.y)) {
        return true;
    }
    return false;
}

Entity UI::createText(std::string text, Vec2 position, SDL_Color color)
{
    Master* master = Master::getInstance();
    Entity entity = master->createEntity();
    TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(entity);
    TransformComponent* transformComponent = master->addComponentOfType<TransformComponent>(entity);
    master->finalizeEntity(entity);

    transformComponent->m_transform = position;
    TextAsset* asset = AssetManager::createText(text, color);
    textureComponent->mRenderSize = asset->getTextSize();
    textureComponent->mAsset = asset;
    textureComponent->mClip = 0;
    textureComponent->mActive = "default";
    return entity;
}

Entity UI::createButton(void (*onClick)(), std::string text, Vec2 position, Vec2 size)
{
    Master* master = Master::getInstance();
    Entity entity = master->createEntity();
    TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(entity);
    TransformComponent* transformComponent = master->addComponentOfType<TransformComponent>(entity);
    UIInputComponent* inputComponent = master->addComponentOfType<UIInputComponent>(entity);
    master->finalizeEntity(entity);

    transformComponent->m_transform = position;
    textureComponent->mRenderSize = size;
    textureComponent->mAsset = AssetManager::getAsset("button");
    textureComponent->mClip = 0;
    textureComponent->mActive = "default";
    Entity textEntity = createText(text, { 0, 0 }, { 0, 0, 0 });

    inputComponent->Update = [textureComponent, transformComponent, inputComponent, onClick]()
    {
        Vec2 mouseLocation = InputManager::getMouseLocation();
        if (InputManager::getActionState(Action::LMB) & InputState::PRESSED)
        {
            if (isPointInsideBox(transformComponent->m_transform, textureComponent->mRenderSize, mouseLocation))
                inputComponent->IsClicked = true;
        }
        else if ((InputManager::getActionState(Action::LMB) & InputState::RELEASED) && inputComponent->IsClicked == true)
        {
            inputComponent->IsClicked = false;
            if (isPointInsideBox(transformComponent->m_transform, textureComponent->mRenderSize, mouseLocation))
                onClick();
        }

    };

    // Center the text of the button
    TextureComponent* textTextureComponent = master->getComponentOfType<TextureComponent>(textEntity);
    TransformComponent* textTransformComponent = master->getComponentOfType<TransformComponent>(textEntity);
    textTransformComponent->m_transform = calculatePositionToCenter(position, size, textTextureComponent->mRenderSize);
    return entity;
}
