#pragma once
#include "SpriteObj.h"
#include <SFML/Graphics.hpp>

class Player;
class Bullet;
class VertexArrayObj;
class Zombie : public SpriteObj
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTypes;

protected:
	Types type;

	Vector2f dir;
	float speed;
	float startDelay=3.f;
	
	int maxHp;
	int hp;

	Vector2f hpBarSize;
	RectangleShape hpBar;

	VertexArrayObj* background;
	Player* player;

public:
	Zombie();
	~Zombie();

	void Init(Player* player);
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	int GetHp() { return hp; }

	void SetBackground(VertexArrayObj* bk);

	void SetType(Types t);
	Types GetType() const;

	void OnHitBullet(int Damage);
};

