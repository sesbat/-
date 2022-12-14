#pragma once
#include <list>
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
	bool trapped;
	float delay = 2.f;
	
	int maxHp;
	int hp;

	Vector2f hpBarSize;
	RectangleShape hpBar;

	VertexArrayObj* background;
	Player* player;

	std::list<SpriteObj> Blood;

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

	void SetTrapped(bool a) { this->trapped = a; }
	void OnHitBullet(int Damage);
	void OnHitBarricade(int Damage,float dt);
	bool GetFalse() { return enabled; }
};

