#include "UiDev2Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev2.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Player.h"
int UiDev2Mgr::shopChoice;
int UiDev2Mgr::nextStageChoice;

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


	Font& font = *RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf");
	textGold = new TextObj();
	textGold->SetFont(font);
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

	nextStage = new TextObj();
	nextStage->SetAll(font, "NEXT STAGE >>", 60, Color::White, {1400, 950});
	uiObjList.push_back(nextStage);

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
	textGold->SetText(formatGold + to_string(Player::GetMoney()));

	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);


	if (cursor->GetPos().x >= 1100 && cursor->GetPos().x <= 1790) // ��, ��
	{
		if (cursor->GetPos().y >= 270 && cursor->GetPos().y <= 460) // GUN ����
		{
			shopChoice = 0;
			choice->SetActive(true);
			choice->SetPos({ 1073 , 257 });
		}
		else if (cursor->GetPos().y >= 620 && cursor->GetPos().y <= 810) // ETC ����
		{
			shopChoice = 1;
			choice->SetActive(true);
			choice->SetPos({ 1073 , 607 });
		}
		else
		{
			choice->SetActive(false);
			shopChoice = 2;
		}
	}
	else
		choice->SetActive(false);


	if (cursor->GetPos().x >= 1400 && cursor->GetPos().x <= 1750 &&
		cursor->GetPos().y >= 960 && cursor->GetPos().y <= 1000)
	{
		nextStage->SetColor(Color::Red);
		nextStageChoice = 1;
	}
	else
	{
		nextStage->SetColor(Color::White);
		nextStageChoice = 0;
	}
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

int UiDev2Mgr::GetNextStageChoice()
{
	return nextStageChoice;
}

void UiDev2Mgr::SetGold(int gold)
{
	
	textGold->SetText(formatGold + to_string(Player::GetMoney()));
}