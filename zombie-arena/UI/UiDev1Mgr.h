#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiDev1Mgr
	:public UiMgr
{
protected:
	string ZombieCount = "Zombie Count : ";
	TextObj* bulletcount;
	TextObj* textZombieCount;
	TextObj* Roundtext;
	SpriteObj* cursor;

	SpriteObj* rifleicon;
	SpriteObj* pistolicon;
	SpriteObj* shotgun;

	TextObj* round;
	TextObj* waiting;
	float waitingCount = 6.f;

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
	static void SetDieImage(bool set);

	static SpriteObj* dieImage;

	static float goWaitingShopCount;
	static TextObj* goWaitingShop;
	static void SetWaitingShop(bool set, float dt);
};

