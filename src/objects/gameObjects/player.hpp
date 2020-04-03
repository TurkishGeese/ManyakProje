#pragma once

#include "gameObject.hpp"

class Player : public GameObject {
public:
    Player();

	void update(float delta) override;
	void input(Action action) override;
private:
    float mPosX;
    float mPosY;

    Action mAction;
};