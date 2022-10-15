#include "Zombie.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/VertexArrayObj.h"
#include "Bullet.h"
const int Zombie::TotalTypes = 3;

using namespace sf;
Zombie::Zombie()
	:hp(100)
{
	hpBarSize.x = hp / 2;
	hpBarSize.y = 5;
	hpBar.setSize({ hpBarSize.x ,hpBarSize.y });
	hpBar.setFillColor(Color::Red);
	hpBar.setPosition({ 1000,1000});
}

Zombie::~Zombie()
{
}

void Zombie::Update(float dt)
{
	SpriteObj::Update(dt);

	startDelay -= dt;
	dir = Utils::Normalize(player->GetPos() - GetPos());
	if (startDelay <= 0) {
		float border = 50.f;
		FloatRect wallBound = background->GetGlobalBounds();
		Vector2f pos;
		pos.x = Utils::Clamp(position.x,
			wallBound.left + border,
			wallBound.left + wallBound.width - border);
		pos.y = Utils::Clamp(position.y,
			wallBound.top + border,
			wallBound.top + wallBound.height - border);
		if (pos != position)
		{
			SetPos(pos);
		}
		Translate(dir * speed * dt);

		float distance = Utils::Distance(player->GetPos(), GetPos());
		if (distance < speed * dt * 0.5f)
		{
			SetPos(player->GetPos());
		}
		else
		{
			float degree = atan2(dir.y, dir.x) * (180 / M_PI);
			sprite.setRotation(degree);
		}

		// �÷��̾� �浹
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnHitZombie(this);
		}
		hpBarSize.x = hp;
		hpBar.setSize({ hpBarSize.x ,hpBarSize.y });
		hpBar.setPosition({ GetPos().x - hp / 2,GetPos().y - 50 });
	}
}

void Zombie::Draw(RenderWindow& window)
{
	window.draw(hpBar);
	for (auto it : Blood)
	{
		it.Draw(window);
	}
	if (startDelay < 0.f)
	{
		window.draw(hpBar);
		SpriteObj::Draw(window);
	}
}


void Zombie::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Zombie::Init(Player* player)
{
	this->player = player;
	SetOrigin(Origins::MC);

	SpriteObj::Init();
}

void Zombie::Reset()
{
	SpriteObj::Reset();

	dir = { 1, 0 };
	hp = maxHp;
	Blood.clear();
	SetPos(position);
}

void Zombie::SetType(Types t)
{
	type = t;

	auto resMgr = RESOURCE_MGR;
	switch (type)
	{
	case Zombie::Types::Bloater:
		SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
		speed = 40;
		maxHp = 100;
		break;
	case Zombie::Types::Chaser:
		SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
		speed = 70;
		maxHp = 75;
		break;
	case Zombie::Types::Crawler:
		SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
		speed = 20;
		maxHp = 50;
		break;
	}
}

Zombie::Types Zombie::GetType() const
{
	return type;
}

void Zombie::OnHitBullet(int Damage)
{
	hp -= Damage;

	SpriteObj blood;
	blood.SetTexture(*RESOURCE_MGR->GetTexture("graphics/blood.png"));
	blood.SetActive(true);
	blood.SetPos(position);
	blood.SetOrigin(Origins::MC);

	Blood.push_back(blood);
}
