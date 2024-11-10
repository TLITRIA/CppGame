#pragma once
#include "SpriteComponent_Chap2.h"
#include <vector>

class AnimSpriteComponent_Chap2 : public SpriteComponent_Chap2
{
public:
    AnimSpriteComponent_Chap2(class Actor_Chap2* owner, int drawOrder = 100);

    void Update(float deltaTime) override;
    void SetAnimTextures(std::vector<SDL_Texture*>& textures);
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
    std::vector<SDL_Texture*> mAnimTextures;
    float mCurrFrame;
    float mAnimFPS;
};

