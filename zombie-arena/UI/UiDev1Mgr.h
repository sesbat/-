#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiDev1Mgr
	:public UiMgr
{
protected:
	string ZombieCount = "Zombie Count :"; // "Score : %d"
	TextObj* bulletcount;
	TextObj* textZombieCount;
	SpriteObj* cursor;
public:
	UiDev1Mgr(Scene* scene);
	~UiDev1Mgr();
	virtual void Init()override;
	virtual void Release();
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetZombieCount(int count);
	void SetBulletCount(int current, int mag);

};

