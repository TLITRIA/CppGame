#include "Component_Chap2.h"

#include "Actor_Chap2.h"
Component_Chap2::Component_Chap2(Actor_Chap2* owner, int updateOrder)
	: mOwner(owner) 
	, mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}
Component_Chap2::~Component_Chap2()
{
	mOwner->RemoveComponent(this);
}
void Component_Chap2::Update(float deltaTime)
{
}
