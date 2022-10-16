#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiGunShop : public UiMgr
{
protected:
	string formatGold = "Gold  :  ";
	TextObj* textGold;

	//test
	//string formatGold = "Magazine  :  ";
	TextObj* textMagazine;

	TextObj* pistolName;
	TextObj* shotGunName;
	TextObj* assaultName;

	SpriteObj* shopBackground;
	SpriteObj* cursor;

	SpriteObj* pistol;
	SpriteObj* shotGun;
	SpriteObj* assaultRifle;

	SpriteObj* locking;

	SpriteObj* addMag;
	SpriteObj* subMag;

public:
	UiGunShop(Scene* scene);
	~UiGunShop();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetGold(int gold);

	static int buyMagazine;
};

