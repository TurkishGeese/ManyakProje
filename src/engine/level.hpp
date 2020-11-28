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
	std::vector<InputConfiguration*> mConfigurations;
};