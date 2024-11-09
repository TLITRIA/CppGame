#pragma once

#include <SDL.h>
#include "Component_Chap2.h"
class SpriteComponent_Chap2 : Component_Chap2
{
public:
	SpriteComponent_Chap2(class Actor_Chap2* owner, int drawOrder = 100);
	~SpriteComponent_Chap2();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	void Update(float deltaTime) { Component_Chap2::Update(deltaTime); } 	 // ??
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

	class Actor_Chap2* GetActor() const { return mOwner; } // ?? VS���������� ����
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

