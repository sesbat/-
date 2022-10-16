#include "UiDev2Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev2.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Zombie.h"

int UiDev2Mgr::shopChoice;

UiDev2Mgr::UiDev2Mgr(Scene* scene)
	: UiMgr(scene)
{
}

UiDev2Mgr::~UiDev2Mgr()
{
}

void UiDev2Mgr::Init()
{
	shopBackground = new SpriteObj();
	shopBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/shopBackground.png"));
	shopBackground->SetOrigin(Origins::MC);
	shopBackground->SetPos({ 960, 400 });
	uiObjList.push_back(shopBackground);

	shopInside = new SpriteObj();
	shopInside->SetTexture(*RESOURCE_MGR->GetTexture("graphics/shopInside.png"));
	shopInside->SetOrigin(Origins::MC);
	shopInside->SetPos({ 960, 600 });
	uiObjList.push_back(shopInside);


	textGold = new TextObj();
	textGold->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	textGold->GetSfmlText().setCharacterSize(60);
	textGold->GetSfmlText().setFillColor({ 255, 215, 0 });
	textGold->GetSfmlText().setPosition({ 1500, 50 });
	uiObjList.push_back(textGold);

	merChant = new SpriteObj();
	merChant->SetTexture(*RESOURCE_MGR->GetTexture("graphics/merchant.png"));
	merChant->SetOrigin(Origins::TL);
	merChant->SetPos({ 100, 100 });
	uiObjList.push_back(merChant);

	Shop = new SpriteObj();
	Shop->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Menu.png"));
	Shop->SetOrigin(Origins::TL);
	Shop->SetPos({ 0, 0 });
	uiObjList.push_back(Shop);


	choice = new SpriteObj();
	choice->SetTexture(*RESOURCE_MGR->GetTexture("graphics/choice.png"));
	choice->SetOrigin(Origins::TL);
	choice->SetPos({ 0, 0 });
	uiObjList.push_back(choice);


	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);


	UiMgr::Init();
}

void UiDev2Mgr::Release()
{
	UiMgr::Release();
}

void UiDev2Mgr::Reset()
{
	UiMgr::Reset();
	SetGold(0);
}

void UiDev2Mgr::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);


	if (cursor->GetPos().x >= 1100 && cursor->GetPos().x <= 1790) // 좌, 우
	{
		if (cursor->GetPos().y >= 270 && cursor->GetPos().y <= 460) // GUN 상점
		{
			shopChoice = 0;
			choice->SetActive(true);
			choice->SetPos({ 1073 , 257 });
		}
		else if (cursor->GetPos().y >= 620 && cursor->GetPos().y <= 810) // ETC 상점
		{
			shopChoice = 1;
			choice->SetActive(true);
			choice->SetPos({ 1073 , 607 });
		}
		else
			choice->SetActive(false);
	}
	else
		choice->SetActive(false);
}

void UiDev2Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}

int UiDev2Mgr::GetShopChoice()
{
	return shopChoice;
}

void UiDev2Mgr::SetGold(int gold)
{
	textGold->SetText(formatGold + to_string(gold));
}