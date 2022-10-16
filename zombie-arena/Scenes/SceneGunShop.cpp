#include "SceneGunShop.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/VertexArrayObj.h"
#include "../UI/UiGunShop.h"

SceneGunShop::SceneGunShop()
	: Scene(Scenes::GunShop)
{
}

SceneGunShop::~SceneGunShop()
{
}

void SceneGunShop::Init()
{
	Release();

	uiMgr = new UiGunShop(this);
	uiMgr->Init();

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneGunShop::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}

	Scene::Release();
}

void SceneGunShop::Enter()
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

void SceneGunShop::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);

	uiMgr->Reset();
}

void SceneGunShop::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
	}

	for (auto obj : objList)
	{
		obj->SetDevMode(true);
	}

	uiMgr->Update(dt);
}

void SceneGunShop::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	uiMgr->Draw(window);
}
