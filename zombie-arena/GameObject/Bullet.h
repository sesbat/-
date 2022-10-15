#pragma once
#include "SpriteObj.h"
#include <list>

class Zombie;
class VertexArrayObj;
class Bullet : public SpriteObj
{
protected:
	Vector2f dir;
	float speed;
	float range;

	int Damage = 5;
	std::list<Zombie*>* zombies;
	VertexArrayObj* background;
	
public:
	Bullet();
	~Bullet();

	void SetZombieList(std::list<Zombie*>* list) { zombies = list; }
	void Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range = 0.f);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	void SetBackground(VertexArrayObj* bk);
	int GetDamage() { return Damage; }

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	
};

