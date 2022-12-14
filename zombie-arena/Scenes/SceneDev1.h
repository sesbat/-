#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"


class Player;
class VertexArrayObj;
class Zombie;
class Bullet;
class SpriteObj;
class Barricade;
class Gun;
class SceneDev1 : public Scene
{
protected:
	VertexArrayObj* background;
	Player* player;
	list<Zombie*> zombies;
	static int zombieCount;
	SpriteObj* cursor;

	static int currRound;
	
	bool made = false;
	float stack = 0.f;
	list<Barricade*> barricades;
	static int barrcadecount;
	ObjectPool<Bullet> bullets;

	float goShop = 6.f;

public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	static int GetCurrRound() { return currRound; }

	void CreateBackground(int cols, int rows, float quadWidth, float quadHeight);
	void CreateZombies(int count);
	void CreateBarricade();

	static int GetBarricadecount() { return barrcadecount; }
	static void AddBaricount(int a) { barrcadecount+=a; }
	static int GetZombiecount() { return zombieCount; }
	list<Zombie*>* GetZombieList() { return &zombies; }
};

