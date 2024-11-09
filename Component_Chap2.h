#pragma once
class Component_Chap2
{
public:
	Component_Chap2(class Actor_Chap2* owner, int updateOrder = 100);
	virtual ~Component_Chap2();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

	class Actor_Chap2* GetActor() const { return mOwner; }
protected:
	class Actor_Chap2* mOwner;
	int mUpdateOrder = 0;
};
