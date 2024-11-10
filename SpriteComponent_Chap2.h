#pragma once
#include "Component_Chap2.h"

#include <SDL.h>
class SpriteComponent_Chap2 : public Component_Chap2
{
public:
	SpriteComponent_Chap2(class Actor_Chap2* owner, int drawOrder = 100);
	~SpriteComponent_Chap2();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

