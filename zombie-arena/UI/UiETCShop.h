#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiETCShop : public UiMgr
{
	string formatGold = "Gold  :  ";
	TextObj* textGold;

	TextObj* barricadeName;
	TextObj* textBarricade;

	SpriteObj* shopBackground;
	SpriteObj* cursor;

	SpriteObj* barricade;

	SpriteObj* add;
	SpriteObj* sub;

public:
	UiETCShop(Scene* scene);
	~UiETCShop();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetGold(int gold);
	static int buyBarricade;
};

