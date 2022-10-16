#include "Barricade.h"
#include "Zombie.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"

Barricade::Barricade()
	:hp(100)
{
	barricadeHpbarSize.x = hp / 2;
	barricadeHpbarSize.y = 5;
	barricadeHpBar.setSize({ barricadeHpbarSize.x ,barricadeHpbarSize.y });
	barricadeHpBar.setFillColor(Color::Green);
	barricadeHpBar.setPosition({ 1000,1000 });
}

Barricade::~Barricade()
{
}

void Barricade::SetPlayer(Player* player)
{
	this->player = player;
}

void Barricade::Sethp(int hp)
{
	this->hp = hp;
}

void Barricade::OnHitZombie(int damage, float dt)
{
	barricadeDelay -= dt;
	if(barricadeDelay<=0.f)
	{
		hp -= damage;
		barricadeHpbarSize.x = hp / 2;
		barricadeHpbarSize.y = 5;
		barricadeHpBar.setSize({ barricadeHpbarSize.x ,barricadeHpbarSize.y });
		barricadeDelay = 2.f;
	}
}


void Barricade::SetPos(const Vector2f& pos)
{
	position = pos;
	barricadeHpBar.setPosition({pos.x - 25, pos.y - 40});
	SpriteObj::SetPos(pos);
}

void Barricade::Init()
{
	SpriteObj::Init();
}

void Barricade::Update(float dt)
{
	if (hp <= 0)
	{
		SetActive(false);
	}
	SpriteObj::Update(dt);
}

void Barricade::Release()
{
	SpriteObj::Release();
}

void Barricade::Draw(RenderWindow& window)
{
	window.draw(barricadeHpBar);
	SpriteObj::Draw(window);
}
