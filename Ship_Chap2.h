#pragma once
#include "Actor_Chap2.h"

class Ship_Chap2 : public Actor_Chap2
{
public:
	Ship_Chap2(class GameChapt2_2D* game);

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed()const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
};

