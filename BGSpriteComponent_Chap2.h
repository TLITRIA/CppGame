#pragma once
#include "SpriteComponent_Chap2.h"
#include "Math.h"
#include <vector>

class BGSpriteComponent_Chap2 : public SpriteComponent_Chap2
{
public:
	BGSpriteComponent_Chap2(class Actor_Chap2* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	// get/set
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
	
private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

