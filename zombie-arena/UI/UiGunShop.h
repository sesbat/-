#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include <list>

class UiGunShop : public UiMgr
{
protected:
	string formatGold = "Gold  :  ";
	TextObj* textGold;

	TextObj* pistolName;
	TextObj* shotGunName;
	TextObj* assaultName;

	TextObj* assaultUnLock;
	TextObj* shotGunUnLock;

	SpriteObj* shopBackground;
	SpriteObj* cursor;

	SpriteObj* pistol;
	SpriteObj* shotGun;
	SpriteObj* assaultRifle;

	vector<SpriteObj*> locking;
	vector<SpriteObj*> addMag;
	vector<SpriteObj*> subMag;
	vector<SpriteObj*> buy;
	vector<SpriteObj*> magazineEdge;
	vector<TextObj*> textMagazine;
	vector<TextObj*> curPrice;
	vector<TextObj*> allPrice;

	int buyPistolMagazine;
	int buyAssaultMagazine;
	int buyShotGunMagazine;

	int buyCount = 0;

public:
	UiGunShop(Scene* scene);
	~UiGunShop();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetGold(int gold);
};

