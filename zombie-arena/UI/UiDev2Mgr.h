#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiDev2Mgr : public UiMgr
{
protected:
	string formatGold = "Gold  :  ";
	TextObj* textGold;
	SpriteObj* shopInside;
	SpriteObj* shopBackground;
	SpriteObj* merChant;
	SpriteObj* Shop;
	SpriteObj* cursor;
	SpriteObj* choice;

	TextObj* nextStage;

public:
	UiDev2Mgr(Scene* scene);
	~UiDev2Mgr();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetGold(int gold);

	static int shopChoice;
	static int GetShopChoice();

	static int nextStageChoice;
	static int GetNextStageChoice();
};

