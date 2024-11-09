#include "SpriteComponent_Chap2.h"

#include <iostream>
#include <cmath>

#include "Actor_Chap2.h"
#include "GameChapt2_2D.h"

double ToDegree(double radians)
{
#ifndef M_PI
	const double PI = 3.14159265358979323846;
#else
	const double PI = M_PI;
#endif
	return radians * (180.0 / PI);
}

SpriteComponent_Chap2::SpriteComponent_Chap2(Actor_Chap2* owner, int drawOrder)
	: Component_Chap2(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent_Chap2::~SpriteComponent_Chap2()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent_Chap2::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,
			ToDegree(mOwner->GetRotation()	), nullptr, SDL_FLIP_NONE
		);
	}
}

void SpriteComponent_Chap2::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight); // £¿£¿
}
