#include "UiGunShop.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneGunShop.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Player.h"
#include "../GameObject/Gun.h"

UiGunShop::UiGunShop(Scene* scene)
	: UiMgr(scene)
{
}

UiGunShop::~UiGunShop()
{
}

void UiGunShop::Init()
{
	shopBackground = new SpriteObj();
	shopBackground->SetAll(*RESOURCE_MGR->GetTexture("graphics/Shop.png"), { 1920 / 2, 1080 / 2 }, Origins::MC);
	uiObjList.push_back(shopBackground);

	pistol = new SpriteObj();
	pistol->SetAll(*RESOURCE_MGR->GetTexture("graphics/Gun1.png"), { 500, 200 }, Origins::MC);
	uiObjList.push_back(pistol);

	assaultRifle = new SpriteObj();
	assaultRifle->SetAll(*RESOURCE_MGR->GetTexture("graphics/Gun2.png"), { 500, 550 }, Origins::MC);
	uiObjList.push_back(assaultRifle);

	shotGun = new SpriteObj();;
	shotGun->SetAll(*RESOURCE_MGR->GetTexture("graphics/Gun3.png"), { 520, 900 }, Origins::MC);
	uiObjList.push_back(shotGun);

	Font& font = *RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf");
	textGold = new TextObj();
	textGold->SetAll(font, "", 60, { 255, 215, 0 }, { 1350, 0 });
	uiObjList.push_back(textGold);

	pistolName = new TextObj();
	pistolName->SetAll(font, "PISTOL", 40, Color::Black, { 450, 60 });
	uiObjList.push_back(pistolName);

	assaultName = new TextObj();
	assaultName->SetAll(font, "ASSAULT RIFLE", 40, Color::Black, { 370, 440 });
	uiObjList.push_back(assaultName);

	shotGunName = new TextObj();
	shotGunName->SetAll(font, "SHOT GUN", 40, Color::Black, { 420, 810 });
	uiObjList.push_back(shotGunName);

	/******************************* add, sub, buy Texture ******************************/
	Texture& addTex = *RESOURCE_MGR->GetTexture("graphics/add.png");
	Texture& subTex = *RESOURCE_MGR->GetTexture("graphics/minus.png");
	Texture& buyTex = *RESOURCE_MGR->GetTexture("graphics/buy.png");
	Texture& lockingTex = *RESOURCE_MGR->GetTexture("graphics/locking.png");
	Texture& edgeTex = *RESOURCE_MGR->GetTexture("graphics/edge.png");

	for (int i = 0; i < 3; i++)
	{
		textMagazine.push_back(new TextObj());
		curPrice.push_back(new TextObj());
		allPrice.push_back(new TextObj());
		magazineEdge.push_back(new SpriteObj());
		addMag.push_back(new SpriteObj());
		subMag.push_back(new SpriteObj());
		buy.push_back(new SpriteObj());
		locking.push_back(new SpriteObj());
	}

	addMag[0]->SetAll(addTex, { shotGun->GetPos().x * 2 + 100, pistol->GetPos().y }, Origins::MC);
	addMag[1]->SetAll(addTex, { shotGun->GetPos().x * 2 + 100, assaultRifle->GetPos().y }, Origins::MC);
	addMag[2]->SetAll(addTex, { shotGun->GetPos().x * 2 + 100, shotGun->GetPos().y }, Origins::MC);

	locking[0]->SetAll(lockingTex, { assaultRifle->GetPos().x - (assaultRifle->GetSize().x / 2), pistol->GetPos().y }, Origins::ML);
	locking[1]->SetAll(lockingTex, { assaultRifle->GetPos().x - (assaultRifle->GetSize().x / 2), assaultRifle->GetPos().y }, Origins::ML);
	locking[2]->SetAll(lockingTex, { assaultRifle->GetPos().x - (assaultRifle->GetSize().x / 2), shotGun->GetPos().y }, Origins::ML);

	textMagazine[0]->SetAll(font, "", 50, Color::Black, { assaultRifle->GetPos().x + assaultRifle->GetSize().x + 140, pistol->GetPos().y - 30 });
	textMagazine[1]->SetAll(font, "", 50, Color::Black, { assaultRifle->GetPos().x + assaultRifle->GetSize().x + 140, assaultRifle->GetPos().y - 30 });
	textMagazine[2]->SetAll(font, "", 50, Color::Black, { assaultRifle->GetPos().x + assaultRifle->GetSize().x + 140, shotGun->GetPos().y - 30 });

	for (int i = 0; i < addMag.size(); i++)
	{
		textMagazine[i]->SetOrigin(Origins::MC);
		subMag[i]->SetAll(subTex, { addMag[i]->GetPos().x + addMag[i]->GetSize().x, addMag[i]->GetPos().y }, Origins::MC);
		buy[i]->SetAll(buyTex, { subMag[i]->GetPos().x + (subMag[i]->GetSize().x * 2), subMag[i]->GetPos().y }, Origins::MC);
		magazineEdge[i]->SetAll(edgeTex, { subMag[i]->GetPos().x - (subMag[i]->GetSize().x * 2), subMag[i]->GetPos().y }, Origins::MC);
		curPrice[i]->SetAll(font, "", 40, Color::Black, { magazineEdge[i]->GetPos().x - 250, magazineEdge[i]->GetPos().y - 50 });
		allPrice[i]->SetAll(font, "", 35, Color::Black, { magazineEdge[i]->GetPos().x - 250, magazineEdge[i]->GetPos().y + 20 });

		uiObjList.push_back(addMag[i]);
		uiObjList.push_back(subMag[i]);
		uiObjList.push_back(buy[i]);
		uiObjList.push_back(textMagazine[i]);
		uiObjList.push_back(magazineEdge[i]);
		uiObjList.push_back(curPrice[i]);
		uiObjList.push_back(allPrice[i]);
	}

	curPrice[0]->SetText("PRICE : 10");
	curPrice[1]->SetText("PRICE : 20");
	curPrice[2]->SetText("PRICE : 15");

	for (int i = 0; i < locking.size(); i++)
	{
		uiObjList.push_back(locking[i]);
	}
	/*************************************************************************************/

	assaultUnLock = new TextObj();
	assaultUnLock->SetAll(font, "5   0", 60, Color::Black, { 1920 / 2 - 5, locking[1]->GetPos().y + 20 });
	assaultUnLock->SetOrigin(Origins::MC);
	uiObjList.push_back(assaultUnLock);

	shotGunUnLock = new TextObj();
	shotGunUnLock->SetAll(font, "5   0", 60, Color::Black, { 1920 / 2 - 5, locking[2]->GetPos().y + 20 });
	shotGunUnLock->SetOrigin(Origins::MC);
	uiObjList.push_back(shotGunUnLock);

	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	UiMgr::Init();
}

void UiGunShop::Release()
{
	UiMgr::Release();
}

void UiGunShop::Reset()
{
	buyPistolMagazine = 0;
	buyAssaultMagazine = 0;
	buyShotGunMagazine = 0;
	UiMgr::Reset();
}

void UiGunShop::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
	SetGold(0);
	textGold->SetText(formatGold + to_string(Player::GetMoney()));

	textMagazine[0]->SetText(to_string(buyPistolMagazine));
	textMagazine[1]->SetText(to_string(buyAssaultMagazine));
	textMagazine[2]->SetText(to_string(buyShotGunMagazine));

	allPrice[0]->SetText(to_string(pistolmagval * buyPistolMagazine) + " GOLD");
	allPrice[1]->SetText(to_string(assaultmagval * buyAssaultMagazine) + " GOLD");
	allPrice[2]->SetText(to_string(shotgunmagval * buyShotGunMagazine) + " GOLD");

	if (buyCount >= 0)
	{
		locking[0]->SetActive(false);
	}
	if (buyCount >= 1)
	{
		locking[1]->SetActive(false);
		assaultUnLock->SetActive(false);
	}
	if (buyCount >= 2)
	{
		locking[2]->SetActive(false);
		shotGunUnLock->SetActive(false);
	}



	if (Player::GetMoney() >= 50)
	{
		if (cursor->GetPos().y >= locking[0]->GetPos().y - locking[0]->GetSize().y / 2 &&
			cursor->GetPos().y <= locking[0]->GetPos().y + locking[0]->GetSize().y / 2 &&
			cursor->GetPos().x >= locking[0]->GetPos().x - locking[0]->GetSize().x / 2 &&
			cursor->GetPos().x <= locking[0]->GetPos().x + locking[0]->GetSize().x / 2 &&
			buyCount == 0)
		{
			if (InputMgr::GetMouseButtonUp(Mouse::Left))
			{
				Player::SetMoney(-50);
				GUN->UnlockGun(1);
				buyCount++;
			}
		}
		if (cursor->GetPos().y >= locking[1]->GetPos().y - locking[0]->GetSize().y / 2 &&
			cursor->GetPos().y <= locking[1]->GetPos().y + locking[0]->GetSize().y / 2 &&
			cursor->GetPos().x >= locking[1]->GetPos().x - locking[0]->GetSize().x / 2 &&
			cursor->GetPos().x <= locking[1]->GetPos().x + locking[0]->GetSize().x / 2 &&
			buyCount == 1)
		{
			if (InputMgr::GetMouseButtonUp(Mouse::Left))
			{
				Player::SetMoney(-50);
				GUN->UnlockGun(2);
				buyCount++;
			}
		}
	}

	for (int i = 0; i < addMag.size(); i++)
	{
		if (locking[i]->GetPos().y == addMag[i]->GetPos().y && locking[i]->GetActive())
		{

		}
		else
		{
			if (cursor->GetPos().y >= addMag[i]->GetPos().y - addMag[i]->GetSize().y / 2 &&
				cursor->GetPos().y <= addMag[i]->GetPos().y + addMag[i]->GetSize().y / 2 &&
				cursor->GetPos().x >= addMag[i]->GetPos().x - addMag[i]->GetSize().x / 2 &&
				cursor->GetPos().x <= addMag[i]->GetPos().x + addMag[i]->GetSize().x / 2)
			{
				if (InputMgr::GetMouseButton(Mouse::Left))
					addMag[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/addClick.png"));

				if (InputMgr::GetMouseButtonUp(Mouse::Left))
				{
					addMag[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));

					if (cursor->GetPos().y >= addMag[0]->GetPos().y - addMag[0]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[0]->GetPos().y + addMag[0]->GetSize().y / 2)
						buyPistolMagazine++;
					if (cursor->GetPos().y >= addMag[1]->GetPos().y - addMag[1]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[1]->GetPos().y + addMag[1]->GetSize().y / 2)
						buyAssaultMagazine++;
					if (cursor->GetPos().y >= addMag[2]->GetPos().y - addMag[2]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[2]->GetPos().y + addMag[2]->GetSize().y / 2)
						buyShotGunMagazine++;
				}
			}
			if (cursor->GetPos().y >= subMag[i]->GetPos().y - subMag[i]->GetSize().y / 2 &&
				cursor->GetPos().y <= subMag[i]->GetPos().y + subMag[i]->GetSize().y / 2 &&
				cursor->GetPos().x >= subMag[i]->GetPos().x - subMag[i]->GetSize().x / 2 &&
				cursor->GetPos().x <= subMag[i]->GetPos().x + subMag[i]->GetSize().x / 2)
			{
				if (InputMgr::GetMouseButton(Mouse::Left))
					subMag[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minusClick.png"));

				if (InputMgr::GetMouseButtonUp(Mouse::Left))
				{
					subMag[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));

					if (cursor->GetPos().y >= addMag[0]->GetPos().y - addMag[0]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[0]->GetPos().y + addMag[0]->GetSize().y / 2)
						if (buyPistolMagazine > 0)
							buyPistolMagazine--;

					if (cursor->GetPos().y >= addMag[1]->GetPos().y - addMag[1]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[1]->GetPos().y + addMag[1]->GetSize().y / 2)
						if (buyAssaultMagazine > 0)
							buyAssaultMagazine--;

					if (cursor->GetPos().y >= addMag[2]->GetPos().y - addMag[2]->GetSize().y / 2 &&
						cursor->GetPos().y <= addMag[2]->GetPos().y + addMag[2]->GetSize().y / 2)
						if (buyShotGunMagazine > 0)
							buyShotGunMagazine--;
				}
			}
			if (cursor->GetPos().y >= buy[i]->GetPos().y - buy[i]->GetSize().y / 2 &&
				cursor->GetPos().y <= buy[i]->GetPos().y + buy[i]->GetSize().y / 2 &&
				cursor->GetPos().x >= buy[i]->GetPos().x - buy[i]->GetSize().x / 2 &&
				cursor->GetPos().x <= buy[i]->GetPos().x + buy[i]->GetSize().x / 2)
			{
				if (InputMgr::GetMouseButton(Mouse::Left))
					buy[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/buyClick.png"));

				if (InputMgr::GetMouseButtonUp(Mouse::Left))
				{
					buy[i]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/buy.png"));

					if ((cursor->GetPos().y >= buy[0]->GetPos().y - buy[0]->GetSize().y / 2 &&
						cursor->GetPos().y <= buy[0]->GetPos().y + buy[0]->GetSize().y / 2) && Player::GetMoney() >= buyPistolMagazine * pistolmagval)
					{

						Player::SetMoney(-1 * (buyPistolMagazine * pistolmagval));
						GUN->BuyMag(TYPE::PISTOL, buyPistolMagazine);
						buyPistolMagazine = 0;
					}

					if ((cursor->GetPos().y >= buy[1]->GetPos().y - buy[1]->GetSize().y / 2 &&
						cursor->GetPos().y <= buy[1]->GetPos().y + buy[1]->GetSize().y / 2) && Player::GetMoney() >= buyAssaultMagazine * assaultmagval)
					{
						Player::SetMoney(-1 * (buyAssaultMagazine * assaultmagval));
						GUN->BuyMag(TYPE::RIFLE, buyAssaultMagazine);
						buyAssaultMagazine = 0;
						// 골드 변경
						// 아이템 개수 변경
					}

					if ((cursor->GetPos().y >= buy[2]->GetPos().y - buy[2]->GetSize().y / 2 &&
						cursor->GetPos().y <= buy[2]->GetPos().y + buy[2]->GetSize().y / 2) && Player::GetMoney() >= buyShotGunMagazine * shotgunmagval)
					{
						Player::SetMoney(-1 * (buyShotGunMagazine * shotgunmagval));
						GUN->BuyMag(TYPE::SHOTGUN, buyShotGunMagazine);
						buyShotGunMagazine = 0;
						// 골드 변경
						// 아이템 개수 변경
					}
				}
			}
		}
	}
}

void UiGunShop::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}

void UiGunShop::SetGold(int gold)
{
	textGold->SetText(formatGold + to_string(gold));
}
