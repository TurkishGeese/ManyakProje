#pragma once

#include <vector>
#include "gameObject.hpp"
#include "uiObject.hpp"

class Level {

public:
	void update(float delta);
	void render();

	~Level();
protected:
	std::vector<GameObject*> mGameObjects;
	std::vector<UIObject*> mUiObjects;

};