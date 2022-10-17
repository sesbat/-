#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/Player.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/VertexArrayObj.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/ItemGenerator.h"
#include "../UI/UiDev1Mgr.h"
#include "../GameObject/Barricade.h"
#include "../GameObject/Gun.h"

int SceneDev1::currRound = 0;
int SceneDev1::barrcadecount = 0;

void OnCreateBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);

	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->Init();
}

SceneDev1::SceneDev1() : Scene(Scenes::Dev1)
{

}

SceneDev1::~SceneDev1()
{
	
}

void SceneDev1::Init()
{
	Release();

	uiMgr = new UiDev1Mgr(this);
	uiMgr->Init();

	CreateBackground(25 ,14, 50.f, 50.f);

	Vector2i centerPos = FRAMEWORK->GetWindowSize() / 2;
	background->SetPos({ 0, 0 });
	background->SetOrigin(Origins::MC);

	player = new Player();
	player->SetName("Player");
	player->SetTexture(*GetTexture("graphics/player.png"));
	player->SetBulletPool(&bullets);
	player->SetBackground(background);
	objList.push_back(player);


	bullets.OnCreate = OnCreateBullet;
	bullets.Init();


	//ItemGenerator* itemGen = new ItemGenerator();
	//itemGen->SetName("ItemGenerator");
	//AddGameObj(itemGen);

	for (auto obj : objList)
	{
		obj->Init();
	}

	
	//cursor = new SpriteObj();
	//cursor->SetTexture(*GetTexture("graphics/crosshair.png"));
	//cursor->SetOrigin(Origins::MC);
	//uiObjList.push_back(cursor);

	//

	//for (auto obj : uiObjList)
	//{
	//	obj->Init();
	//}
}

void SceneDev1::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}

	bullets.Release();

	Scene::Release();
	player = nullptr;
}

void SceneDev1::Enter()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	player->SetPos( { 0, 0 });

	zombieCount = zombies.size();
	((UiDev1Mgr*)uiMgr)->SetZombieCount(zombieCount);

	currRound++;
}

void SceneDev1::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);

	auto it = zombies.begin();
	while (it != zombies.end())
	{
		objList.remove(*it);
		delete* it;
		it = zombies.erase(it);
	}

	player->Reset();
	bullets.Reset();
	for (auto bar : barricades)
	{
		objList.remove(bar);
		delete bar;
	}
	barricades.clear();
	stack = 0;
	made = false;
	//FindGameObj("ItemGenerator")->Reset();

	uiMgr->Reset();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	
	stack += dt;

	if (stack >= 6.f&&!made)
	{
		CreateZombies(10);
		made = true;
	}

	//cout<<(int)GUN->PrintCurrentMode()<<endl;
	sf::Vector2f mouseworldPos = FRAMEWORK->GetWindow().mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), worldView);	

	Vector2f dir;
	dir.x = mouseworldPos.x - player->GetPos().x;
	dir.y = mouseworldPos.y - player->GetPos().y;

	float r = 0.5;
	Vector2f camPoslen;
	camPoslen.x= dir.x * r;
	camPoslen.y = dir.y* r;


	Vector2f realcam;
	realcam.x = camPoslen.x + player->GetPos().x;
	realcam.y = camPoslen.y + player->GetPos().y;

	worldView.setCenter(realcam);
	((UiDev1Mgr*)uiMgr)->SetBulletCount(GUN->PrintCurrentammo(),GUN->PrintMagCount());

	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		exit(1);
	}
	if (InputMgr::GetKeyDown(Keyboard::P)&&barrcadecount>0)
	{
		barrcadecount--;
		CreateBarricade();
	}
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
	}

	if (InputMgr::GetKeyDown(Keyboard::Num1)) {
		GUN->Change(0);
	}
	else if (InputMgr::GetKeyDown(Keyboard::Num2)) {
		GUN->Change(1);
	}
	else if (InputMgr::GetKeyDown(Keyboard::Num3)) {
		GUN->Change(2);
	}
	
	zombieCount = zombies.size();
	for (auto zombie : zombies)
	{
		if (!zombie->GetActive())
		{
			zombieCount--;
			((UiDev1Mgr*)uiMgr)->SetZombieCount(zombieCount);
		}
	}

	for (auto& v : zombies) {
		if (v->GetActive()) {
			break;
		}
		else if (!v->GetActive() && v == zombies.back()) {
			SCENE_MGR->ChangeScene(Scenes::Dev2);
			return;
		}
	}

	// test
	if (player->GetActive())
	{
		UiDev1Mgr::SetDieImage(false);
	}
	if (InputMgr::GetKeyDown(Keyboard::E))
	{
		player->SetActive(false);
		UiDev1Mgr::SetRound(true);
		UiDev1Mgr::SetDieImage(true);
	}

	/*if (!(bullets.Get()->IsClear()))
	{
		
	}*/
		/*for (auto zombie : zombies)
		{
			if (barricade != nullptr&&zombie->GetGlobalBounds().intersects(barricade->GetSprite().getGlobalBounds()))
			{
				zombie->OnHitBarricade(10,dt);
			}
			else {
				zombie->SetTrapped(false);
			}
		}*/
	for (auto zombie : zombies)
	{
		for(auto bar : barricades)
		if (bar != nullptr && zombie->GetGlobalBounds().intersects(bar->GetSprite().getGlobalBounds()))
		{
			if(bar->GetActive()) 
			{
				zombie->OnHitBarricade(10, dt);
				bar->OnHitZombie(10, dt);
			}
		}
		else {
			zombie->SetTrapped(false);
		}
	}
		
		
	bullets.Update(dt);
	uiMgr->Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	const auto& bulletList = bullets.GetUseList();
	for (auto bullet : bulletList)
	{
		bullet->Draw(window);
	}
	for (auto bar : barricades)
	{
		bar->Draw(window);
	}
	uiMgr->Draw(window);
}

void SceneDev1::CreateBackground(int cols, int rows, float quadWidth, float quadHeight)
{
	if (background == nullptr)
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/background_sheet.png"));
		objList.push_back(background);
	}

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(cols * rows * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{ 0, 0 },
		{ quadWidth, 0 },
		{ quadWidth, quadHeight },
		{ 0, quadHeight },
	};

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if ((i == 0 || i == rows - 1) || (j == 0 || j == cols - 1))
			{
				texIndex = 3;
			}

			int quadIndex = i * cols + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.y += quadHeight * texIndex;
			}
			currPos.x += 50;
		}
		currPos.x = startPos.x;
		currPos.y += 50;
	}
}

void SceneDev1::CreateZombies(int count)
{
	auto winSize = FRAMEWORK->GetWindowSize();
	FloatRect rect(200.f, 200.f, winSize.x - 400.f, winSize.y - 400.f);
	float x, y;

	Vector2f point;

	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = new Zombie();
		zombie->SetType(
			(Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));

		zombie->Init(player);

		point.x = Utils::RandomRange(-1.0f, 1.0f);
		point.y = Utils::RandomRange(-1.0f, 1.0f);
		point = Utils::Normalize(point);
		point *= Utils::RandomRange(0.f, 500.f);
		zombie->SetPos(point);

		zombie->SetBackground(background);
		
		objList.push_back(zombie);
		zombies.push_back(zombie);;
	}
}


void SceneDev1::CreateBarricade()
{
	Barricade* temp = new Barricade();
	temp->SetTexture(*GetTexture("graphics/barricade.png"));
	temp->SetPos(player->GetPos());
	temp->SetPlayer(player);
	temp->SetOrigin(Origins::MC);
	temp->SetActive(true);
	objList.push_back(temp);
	barricades.push_back(temp);
}
