#include "Actor_Chap2.h"

#include "GameChapt2_2D.h"
#include "Component_Chap2.h"
#include <algorithm>

Actor_Chap2::Actor_Chap2(GameChapt2_2D* game)
	: mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor_Chap2::~Actor_Chap2()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor_Chap2::Update(float deltaTime)
{
	if (mState == EActive)
	{
		//std::cout << __FUNCTION__ << ":" << __LINE__ << __cplusplus << "\n";
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime); 
	}
}

void Actor_Chap2::UpdateActor(float deltaTime)
{
}

void Actor_Chap2::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		//std::cout << __FUNCTION__ << ":" << __LINE__ << "\n";
		comp->Update(deltaTime);
	}
}

void Actor_Chap2::AddComponent(Component_Chap2* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor_Chap2::RemoveComponent(Component_Chap2* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
