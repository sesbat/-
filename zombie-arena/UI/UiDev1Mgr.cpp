#include "UiDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Zombie.h"
#include "../Framework/Framework.h"

SpriteObj* UiDev1Mgr::dieImage = new SpriteObj();
TextObj* UiDev1Mgr::round = new TextObj();

UiDev1Mgr::UiDev1Mgr(Scene* scene)
	:UiMgr(scene)
{
}

UiDev1Mgr::~UiDev1Mgr()
{
}

void UiDev1Mgr::Init()
{
	textZombieCount = new TextObj();
	textZombieCount->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	textZombieCount->GetSfmlText().setCharacterSize(75);
	textZombieCount->GetSfmlText().setPosition({ 50,50 });
	uiObjList.push_back(textZombieCount);

	Roundtext = new TextObj();
	Roundtext->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	Roundtext->GetSfmlText().setCharacterSize(75);
	Roundtext->GetSfmlText().setPosition({ (float)FRAMEWORK->GetWindowSize().x/2,50.f});
	Roundtext->SetText("Round : " + to_string(SceneDev1::GetCurrRound()));
	uiObjList.push_back(Roundtext);

	bulletcount = new TextObj();
	bulletcount->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	bulletcount->GetSfmlText().setCharacterSize(75);
	bulletcount->GetSfmlText().setPosition({ 50,850});
	//bulletcount->SetText("test");
	uiObjList.push_back(bulletcount);

	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	pistolicon = new SpriteObj();
	pistolicon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun1icon.png"));
	pistolicon->SetOrigin(Origins::MC);
	pistolicon->SetPos({ 100,850 - 60 });

	rifleicon = new SpriteObj();
	rifleicon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun2icon.png"));
	rifleicon->SetOrigin(Origins::MC);
	rifleicon->SetPos({ 100,850 - 60 });

	shotgun = new SpriteObj();
	shotgun->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Gun3icon.png"));
	shotgun->SetOrigin(Origins::MC);
	shotgun->SetPos({ 100,850 - 60 });
	

	dieImage->SetAll(*RESOURCE_MGR->GetTexture("graphics/DieImage.png"), {1920 / 2, 1080 / 2}, Origins::MC);
	dieImage->SetActive(false);
	uiObjList.push_back(dieImage);

	round->SetAll(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"), "", 100, Color::White, { 1920 / 2 - 200, 1080 / 2 - 300 });
	round->SetActive(false);
	uiObjList.push_back(round);

	UiMgr::Init();
	
}

void UiDev1Mgr::Release()
{
	UiMgr::Release();
}

void UiDev1Mgr::Reset()
{
	UiMgr::Reset();
	SetZombieCount(0);
}

void UiDev1Mgr::Update(float dt)
{
	UiMgr::Update(dt);
	Roundtext->SetText("Round : " + to_string(SceneDev1::GetCurrRound()));
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
}

void UiDev1Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
	if (GUN->PrintCurrent() == 0)
		window.draw(pistolicon->GetSprite());
	else if (GUN->PrintCurrent() == 1) {
		window.draw(rifleicon->GetSprite());
	}
	else if (GUN->PrintCurrent() == 2) {
		window.draw(shotgun->GetSprite());
	}
}

void UiDev1Mgr::SetZombieCount(int count)
{
	textZombieCount->SetText(ZombieCount + to_string(count));
} 
void UiDev1Mgr::SetBulletCount(int current, int mag)
{
	bulletcount->SetText(to_string(current) + "/" + to_string(mag));
}

void UiDev1Mgr::SetDieImage(bool set)
{
	dieImage->SetActive(set);
}

void UiDev1Mgr::SetRound(bool set)
{
	round->SetText("DAY  -  " + to_string(SceneDev1::GetCurrRound()));
	round->SetActive(set);
}
