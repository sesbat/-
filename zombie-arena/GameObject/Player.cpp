#include "Player.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "Bullet.h"
#include <iostream>
#include <limits>
#include "Pickup.h"
#include "VertexArrayObj.h"
#include "Zombie.h"
#include "../Scenes/SceneMgr.h"
#include "../UI/UiDev1Mgr.h"
#include "../Framework/SoundMgr.h"

int Player::mag = 10;
int Player::money = 200;


Player::Player()
	: speed(500), accelation(1000), deaccelation(1000), bulletPool(nullptr), reloadTime(1.5f), reloadTimer(0.f), isReloading(false),
	fireMode(FireModes::Manual), semiTotal(3), intervalManual(0.1f), intervalSemiauto(0.1f), intervalAuto(0.1f),
	isSemiFiring(false), semiCount(0)
{
}

Player::~Player()
{
}

void Player::SetBulletPool(ObjectPool<Bullet>* ptr)
{
	bulletPool = ptr;
}

void Player::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Player::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();

	scene = SCENE_MGR->GetCurrScene();
	uiMgr = scene->GetUiMgr();
}

void Player::Reset()
{
	SpriteObj::Reset();

	direction = { 1.f, 0.f };
	velocity = { 0.f, 0.f };
}

void Player::Update(float dt)
{
	Scene* scene = SCENE_MGR->GetCurrScene();
	SpriteObj::Update(dt);

	RenderWindow& window = FRAMEWORK->GetWindow();
	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f mouseWorldPos = scene->ScreenToWorldPos(mousePos);

	look = Utils::Normalize(mouseWorldPos - GetPos());
	float degree = atan2(look.y, look.x) * (180.f / M_PI);
	sprite.setRotation(degree);

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);

	// ����
	//velocity += direction * accelation * dt;
	/*if (Utils::Magnitude(velocity) > speed)
	{
		velocity = Utils::Normalize(velocity) * speed;
	}*/

	/*if (direction.x == 0.f)
	{
		if (velocity.x > 0.f)
		{
			velocity.x -= deaccelation * dt;
			if (velocity.x < 0.f)
				velocity.x = 0.f;
		}
		if (velocity.x < 0.f)
		{
			velocity.x += deaccelation * dt;
			if (velocity.x > 0.f)
				velocity.x = 0.f;
		}
	}

	if (direction.y == 0.f)
	{
		if (velocity.y > 0.f)
		{
			velocity.y -= deaccelation * dt;
			if (velocity.y < 0.f)
				velocity.y = 0.f;
		}
		if (velocity.y < 0.f)
		{
			velocity.y += deaccelation * dt;
			if (velocity.y > 0.f)
				velocity.y = 0.f;
		}
	}
	*/
	Translate(speed * direction * dt);

	// �� �浹
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
		velocity = { 0, 0 };
	}

	// �߻� �ڵ�
	if (bulletPool == nullptr)
		return;

	fireTimer += dt;

	if (isReloading)
	{
		reloadTimer += dt;
		if (reloadTimer > GUN->PrintReloadTime())
		{
			isReloading = false;
			reloadTimer = 0.f;
			cout << "Reload End" << endl;
		}
		else
		{
			return;
		}
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::R))
	{
		Reload();
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::B))
	{
		GUN->SetFireMode();
	}

	//firemode �Ѱܼ� ���̾��忡 �°� ���?
	
	switch ((int)GUN->PrintCurrentMode())
	{
	case 2:
		if (fireTimer > intervalManual &&
			InputMgr::GetMouseButtonDown(Mouse::Button::Left))
		{
			Fire();
		}
		break;
	case 1:
		if (fireTimer > intervalSemiauto &&
			(isSemiFiring || InputMgr::GetMouseButtonDown(Mouse::Button::Left)))
		{
			if (semiCount == 0)
			{
				isSemiFiring = true;
			}

			semiCount++;
			cout << semiCount << endl;
			if (semiCount <= semiTotal && currentAmmo > 0)
			{
				Fire();
			}
			else
			{
				isSemiFiring = false;
				fireTimer = 0.f;
				semiCount = 0;
			}
		}
		break;
	case 0:
		if (fireTimer > intervalAuto &&
			InputMgr::GetMouseButton(Mouse::Button::Left))
		{
			Fire();
		}
		break;
	}


}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::Fire()
{
	if ( GUN->PrintCurrentammo() == 0)
	{
		return;
	}
	

	Vector2f startPos = position;
	startPos += look * 25.f;
	Bullet* bullet = bulletPool->Get();
	bullet->SetBackground(background);
	bullet->Fire(startPos, look, 1000, 500);
	GUN->shoot();
	fireTimer = 0.f;

	if (GUN->PrintCurrent() == 2) {
		Bullet* bullet1 = bulletPool->Get();
		Bullet* bullet2 = bulletPool->Get();
		bullet1->SetBackground(background);
		bullet2->SetBackground(background);
		bullet1->Fire(startPos, { look.x + 10,look.y },1000, 500);
		bullet2->Fire(startPos, { look.x - 10,look.y }, 1000, 500);

	}
	SOUND_MGR->Play("sound/shoot.wav", false);

}

void Player::Reload()
{
	if (GUN->PrintMagCount() > 0&&GUN->PrintCurrentammo() != GUN->PrintCurrentMaxAmmo()) {
		isReloading = true;
		reloadTimer = 0.f;


		GUN->Reload();

		currentAmmo = 8;


		cout << "Reload Start" << endl;

		SOUND_MGR->Play("sound/reload.wav", false);
	}

}

void Player::OnPickupItem(Pickup* item)
{
	switch (item->GetType())
	{
	case Pickup::Types::Ammo:
		//	ammo += item->GetValue();
		break;
	case Pickup::Types::Health:
		// ü�� ����
		break;
	}
}

void Player::OnHitZombie(Zombie* zombie)
{
	// ü�� ����
	// (����)
}
