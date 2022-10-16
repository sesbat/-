#pragma once
#include "SpriteObj.h"

class Zombie;
class Player;
class Barricade
	:public SpriteObj
{
protected:
	Player* player;

	Vector2f position;
	RectangleShape barricadeHpBar;
	Vector2f barricadeHpbarSize;
	float barricadeDelay = 2.f;
	int hp;
public:
	Barricade();
	~Barricade();

	void SetPlayer(Player* player);
	void Sethp(int hp);
	int Gethp() { return hp; }
	void OnHitZombie(int damage,float dt);

	virtual void SetPos(const Vector2f& pos)override;
	virtual void Init()override;
	virtual void Update(float dt)override;
	virtual void Release()override;
	virtual void Draw(RenderWindow& window)override;
};

