#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiDev2Mgr : public UiMgr
{
protected:
	string formatGold = "Gold : ";
	TextObj* textGold;
	SpriteObj* shopInside;
	SpriteObj* shopBackground;
	SpriteObj* merChant;
	SpriteObj* Shop;
	SpriteObj* cursor;
	SpriteObj* choice;

public:
	UiDev2Mgr(Scene* scene);
	~UiDev2Mgr();
	virtual void Init()override;
	virtual void Release();
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetGold(int gold);

	static int shopChoice;
	static int GetShopChoice();
};

