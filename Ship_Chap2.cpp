#include "Ship_Chap2.h"
#include "GameChapt2_2D.h"
#include "AnimSpriteComponent_Chap2.h"


#include <iostream>
Ship_Chap2::Ship_Chap2(GameChapt2_2D* game)
	: Actor_Chap2(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated spirte component
	AnimSpriteComponent_Chap2* asc = new AnimSpriteComponent_Chap2(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimTextures(anims);
}

void Ship_Chap2::UpdateActor(float deltaTime)
{
	Actor_Chap2::UpdateActor(deltaTime); // Actor_Chap2::Update(deltaTime); //  Ô­À´ÊÇ
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}

void Ship_Chap2::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;

	// rigth/left
	
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
}
