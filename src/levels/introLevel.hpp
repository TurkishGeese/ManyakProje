#pragma once

#include "level.hpp"

class IntroLevel : public Level {

public:
	IntroLevel();

	void preUpdate() override;
};