#include "SceneDev2.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/VertexArrayObj.h"
#include "../UI/UiDev2Mgr.h"

SceneDev2::SceneDev2()
	: Scene(Scenes::Dev2)
{

}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	Release();

	uiMgr = new UiDev2Mgr(this);
	uiMgr->Init();

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev2::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}

	Scene::Release();
}

void SceneDev2::Enter()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void SceneDev2::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);

	uiMgr->Reset();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		exit(1);
	}

	if (InputMgr::GetMouseButtonUp(Mouse::Button::Left))
	{
		if (UiDev2Mgr::GetShopChoice() == 0)
		{
			SCENE_MGR->ChangeScene(Scenes::GunShop);
		}
		else if (UiDev2Mgr::GetShopChoice() == 1)
		{
			SCENE_MGR->ChangeScene(Scenes::ETCShop);
		}
		else if (UiDev2Mgr::GetNextStageChoice() == 1)
		{
			SCENE_MGR->ChangeScene(Scenes::Dev1);
		}
	}

	for (auto obj : objList)
	{
		obj->SetDevMode(true);
	}

	uiMgr->Update(dt);
}

void SceneDev2::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	uiMgr->Draw(window);
}
