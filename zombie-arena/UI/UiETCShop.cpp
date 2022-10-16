#include "UiETCShop.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneETCShop.h"
#include "../Framework/InputMgr.h"

int UiETCShop::buyBarricade = 0;

UiETCShop::UiETCShop(Scene* scene)
	: UiMgr(scene)
{
}

UiETCShop::~UiETCShop()
{
}

void UiETCShop::Init()
{
	shopBackground = new SpriteObj();
	shopBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Shop.png"));
	shopBackground->SetOrigin(Origins::MC);
	shopBackground->SetPos({ 1920 / 2, 1080 / 2 });
	uiObjList.push_back(shopBackground);

	Font& font = *RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf");
	textGold = new TextObj();
	textGold->SetFont(font);
	textGold->GetSfmlText().setCharacterSize(60);
	textGold->GetSfmlText().setFillColor({ 255, 215, 0 });
	textGold->GetSfmlText().setPosition({ 1350, 50 });
	uiObjList.push_back(textGold);

	barricadeName = new TextObj();
	barricadeName->SetAll(font, "BARRICADE", 40, Color::Black, {400, 150});
	uiObjList.push_back(barricadeName);

	add = new SpriteObj();
	add->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));
	add->SetPos({ 1200, 300 });
	add->SetOrigin(Origins::MC);
	uiObjList.push_back(add);

	sub = new SpriteObj();
	sub->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));
	sub->SetPos({ 1300, 300});
	sub->SetOrigin(Origins::MC);
	uiObjList.push_back(sub);

	barricade = new SpriteObj();
	barricade->SetTexture(*RESOURCE_MGR->GetTexture("graphics/barricadeShop.png"));
	barricade->SetPos({500, 300});
	barricade->SetOrigin(Origins::MC);
	uiObjList.push_back(barricade);

	textBarricade = new TextObj();
	textBarricade->SetAll(font, "BARRICADE COUNT : " + to_string(buyBarricade), 50, Color::Black, { 600, 600 });
	uiObjList.push_back(textBarricade);

	cursor = new SpriteObj();;
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	UiMgr::Init();
}

void UiETCShop::Release()
{
	UiMgr::Release();
}

void UiETCShop::Reset()
{
	UiMgr::Reset();
}

void UiETCShop::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);

	// test
	SetGold(0);
	textBarricade->SetText("BARRICADE COUNT : " + to_string(buyBarricade));

	if (InputMgr::GetMouseButton(Mouse::Left))
	{
		if (cursor->GetPos().y >= add->GetPos().y - 50 && cursor->GetPos().y <= add->GetPos().y + 50 &&
			cursor->GetPos().x >= add->GetPos().x - 50 && cursor->GetPos().x <= add->GetPos().x + 50)
		{
			add->SetTexture(*RESOURCE_MGR->GetTexture("graphics/addClick.png"));
		}
		if (cursor->GetPos().y >= sub->GetPos().y - 50 && cursor->GetPos().y <= sub->GetPos().y + 50 &&
			cursor->GetPos().x >= sub->GetPos().x - 50 && cursor->GetPos().x <= sub->GetPos().x + 50)
		{
			sub->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minusClick.png"));
		}
	}
	if (InputMgr::GetMouseButtonUp(Mouse::Left))
	{
		add->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));
		sub->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));

		if (cursor->GetPos().y >= add->GetPos().y - 50 && cursor->GetPos().y <= add->GetPos().y + 50 &&
			cursor->GetPos().x >= add->GetPos().x - 50 && cursor->GetPos().x <= add->GetPos().x + 50)
			buyBarricade++;

		if (cursor->GetPos().y >= sub->GetPos().y - 50 && cursor->GetPos().y <= sub->GetPos().y + 50 &&
			cursor->GetPos().x >= sub->GetPos().x - 50 && cursor->GetPos().x <= sub->GetPos().x + 50 &&
			buyBarricade > 0)
			buyBarricade--;
	}

}

void UiETCShop::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}

void UiETCShop::SetGold(int gold)
{
	textGold->SetText(formatGold + to_string(gold));
}
