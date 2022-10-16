#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include <list>

enum class FireModes
{
	Manual,
	Semi,
	Auto,
};

class Bullet;
class Pickup;
class VertexArrayObj;
class Zombie;
class Scene;
class UiMgr;

class Player : public SpriteObj
{
protected:
	Vector2f look;	
	Vector2f direction;	
	float speed;	
	float accelation;		
	float deaccelation;		

	Vector2f velocity; 

	VertexArrayObj* background;

	ObjectPool<Bullet>* bulletPool;

	Scene* scene;
	UiMgr* uiMgr;

	int currentAmmo;

	bool isReloading;
	float reloadTime;
	float reloadTimer;

	float fireTimer;
	FireModes fireMode;
	int semiTotal;
	int semiCount;

	float intervalManual;
	float intervalSemiauto;
	float intervalAuto;
	bool isSemiFiring;

	float itemTimer;

	static int mag;
	static int money;

public:
	Player();
	virtual ~Player();
	
	void SetBulletPool(ObjectPool<Bullet>* ptr);
	void SetBackground(VertexArrayObj* bk);

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
	void Reload();

	Vector2f GetLook() { return look; }
	void OnPickupItem(Pickup* item);
	void OnHitZombie(Zombie* zombie);

	int GetMagCount() { return mag; }
	int GetCurrnetbulletCount() { return currentAmmo; }
	static void SetMoney(int a) { money += a; }
	static int GetMoney() { return money; }
};

