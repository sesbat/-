#include "UiDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Zombie.h"
#include "../Framework/Framework.h"

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

	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
}

void UiDev1Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}

void UiDev1Mgr::SetZombieCount(int count)
{
	textZombieCount->SetText(ZombieCount + to_string(count));
} 
void UiDev1Mgr::SetBulletCount(int current, int mag)
{
	bulletcount->SetText(to_string(current) + "/" + to_string(mag));
}
