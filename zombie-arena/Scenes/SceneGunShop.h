#pragma once
#include "Scene.h"
#include "../GameObject/Object.h"

class SpriteObj;
class Object;

class SceneGunShop : public Scene
{
protected:


public:
	SceneGunShop();
	virtual ~SceneGunShop();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

