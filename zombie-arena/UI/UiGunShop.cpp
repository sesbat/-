#include "UiGunShop.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev2.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Zombie.h"

int UiGunShop::buyMagazine = 0;

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
	shopBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Shop.png"));
	shopBackground->SetOrigin(Origins::MC);
	shopBackground->SetPos({1920 / 2, 1080 / 2});
	uiObjList.push_back(shopBackground);

	pistol = new SpriteObj();;
	pistol->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun1.png"));
	pistol->SetPos({500, 200});
	pistol->SetOrigin(Origins::MC);
	uiObjList.push_back(pistol);

	assaultRifle = new SpriteObj();;
	assaultRifle->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun2.png"));
	assaultRifle->SetPos({ 500, 550 });
	assaultRifle->SetOrigin(Origins::MC);
	uiObjList.push_back(assaultRifle);

	shotGun = new SpriteObj();;
	shotGun->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun3.png"));
	shotGun->SetPos({ 500, 900 });
	shotGun->SetOrigin(Origins::MC);
	uiObjList.push_back(shotGun);



	Font& font = *RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf");
	textGold = new TextObj();
	textGold->SetFont(font);
	textGold->GetSfmlText().setCharacterSize(60);
	textGold->GetSfmlText().setFillColor({ 255, 215, 0 });
	textGold->GetSfmlText().setPosition({ 1350, 50 });
	uiObjList.push_back(textGold);

	/**************** Test Magazine Add, Sub ******************/
	textMagazine = new TextObj();
	textMagazine->SetAll(font, "Magazine : ", 50, Color::Black, {900, 900});
	uiObjList.push_back(textMagazine);
	/**********************************************************/
	
	pistolName = new TextObj();
	pistolName->SetAll(font, "PISTOL", 40, Color::Black, {450, 60});
	uiObjList.push_back(pistolName);

	assaultName = new TextObj();
	assaultName->SetAll(font, "ASSAULT RIFLE", 40, Color::Black, { 370, 440 });
	uiObjList.push_back(assaultName);

	shotGunName = new TextObj();
	shotGunName->SetAll(font, "SHOT GUN", 40, Color::Black, {420, 810});
	uiObjList.push_back(shotGunName);


	/************** locking image ****************/
	locking = new SpriteObj();
	locking->SetTexture(*RESOURCE_MGR->GetTexture("graphics/locking.png"));
	locking->SetOrigin(Origins::TL);
	locking->SetPos({ 300, 400 });
	uiObjList.push_back(locking);
	/*********************************************/

	addMag = new SpriteObj();
	addMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));
	addMag->SetPos({500, 500});
	addMag->SetOrigin(Origins::MC);
	uiObjList.push_back(addMag);

	subMag = new SpriteObj();
	subMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));
	subMag->SetPos({ 600, 500 });
	subMag->SetOrigin(Origins::MC);
	uiObjList.push_back(subMag);

	cursor = new SpriteObj();;
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
	UiMgr::Reset();
}

void UiGunShop::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
	SetGold(0);

	/****************************** Test *****************************/
	textMagazine->SetText("Magazine : " + to_string(buyMagazine));
	/******************************************************************/
	
	// MouseClick +, -
	if (InputMgr::GetMouseButton(Mouse::Left))
	{
		if (cursor->GetPos().y >= addMag->GetPos().y - 50 && cursor->GetPos().y <= addMag->GetPos().y + 50 &&
			cursor->GetPos().x >= addMag->GetPos().x - 50 && cursor->GetPos().x <= addMag->GetPos().x + 50)
		{
				addMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/addClick.png"));
		}
		if (cursor->GetPos().y >= subMag->GetPos().y - 50 && cursor->GetPos().y <= subMag->GetPos().y + 50 &&
			cursor->GetPos().x >= subMag->GetPos().x - 50 && cursor->GetPos().x <= subMag->GetPos().x + 50)
		{
				subMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minusClick.png"));
		}
	}
	if (InputMgr::GetMouseButtonUp(Mouse::Left) )
	{
		addMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));
		subMag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));

		if (cursor->GetPos().y >= addMag->GetPos().y - 50 && cursor->GetPos().y <= addMag->GetPos().y + 50 &&
			cursor->GetPos().x >= addMag->GetPos().x - 50 && cursor->GetPos().x <= addMag->GetPos().x + 50 )
			buyMagazine++;

		if ((cursor->GetPos().y >= subMag->GetPos().y - 50 && cursor->GetPos().y <= subMag->GetPos().y + 50 &&
			cursor->GetPos().x >= subMag->GetPos().x - 50 && cursor->GetPos().x <= subMag->GetPos().x + 50) && buyMagazine > 0)
			buyMagazine--;
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
