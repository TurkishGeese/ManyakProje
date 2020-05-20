#pragma once

#include <vector>
#include "gameObject.hpp"
#include "uiObject.hpp"
#include "inputConfiguration.hpp"

class Level {

public:
	void virtual preUpdate();
	void update(float delta);
	void render();

	virtual ~Level();
protected:
	std::vector<GameObject*> mGameObjects;
	std::vector<UIObject*> mUiObjects;
	std::vector<InputConfiguration*> mConfigurations;
};