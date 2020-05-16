#pragma once

#include "gameObject.hpp"

class Player : public GameObject {
public:
    Player();

	void update(float delta) override;

    float getLastDelta();
private:
    float mPosX;
    float mPosY;
    float mDelta;
};