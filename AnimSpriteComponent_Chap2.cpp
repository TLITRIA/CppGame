#include "AnimSpriteComponent_Chap2.h"
#include "Math.h"


AnimSpriteComponent_Chap2::AnimSpriteComponent_Chap2(Actor_Chap2* owner, int drawOrder)
	: SpriteComponent_Chap2(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent_Chap2::Update(float deltaTime)
{
	SpriteComponent_Chap2::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		mCurrFrame += mAnimFPS * deltaTime;
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent_Chap2::SetAnimTextures(std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
