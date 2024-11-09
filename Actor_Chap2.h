#pragma once
#include <vector>
#include "Math.h"
#include "Vector2.h"

class Actor_Chap2
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor_Chap2(class GameChapt2_2D* game);
	virtual ~Actor_Chap2();

	void Update(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	void UpdateComponents(float deltaTime);
	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& position) { mPosition = position; }
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	float GetScale() const { return mScale; }
	void SetScale(int scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	class GameChapt2_2D* GetGame(){ return mGame; }

	// Add / remove componnets
	void AddComponent(class Component_Chap2* component);
	void RemoveComponent(class Component_Chap2* component);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	std::vector<class Component_Chap2*> mComponents;
	class GameChapt2_2D* mGame;
};

