#include "UiETCShop.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneETCShop.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/Player.h"
#include "../Scenes/SceneDev1.h"

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
	shopBackground->SetAll(*RESOURCE_MGR->GetTexture("graphics/Shop.png"), { 1920 / 2, 1080 / 2 }, Origins::MC);
	uiObjList.push_back(shopBackground);

	Font& font = *RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf");

	textGold = new TextObj();
	textGold->SetAll(font, "", 60, { 255, 215, 0 }, { 1350, 20 });
	uiObjList.push_back(textGold);

	barricadeName = new TextObj();
	barricadeName->SetAll(font, "BARRICADE", 40, Color::Black, {400, 150});
	uiObjList.push_back(barricadeName);

	barricade = new SpriteObj();
	barricade->SetAll(*RESOURCE_MGR->GetTexture("graphics/barricadeShop.png"), { 500, 300 }, Origins::MC);
	uiObjList.push_back(barricade);

	add = new SpriteObj();
	add->SetAll(*RESOURCE_MGR->GetTexture("graphics/add.png"), { barricade->GetPos().x * 2 + 100, barricade->GetPos().y }, Origins::MC);
	uiObjList.push_back(add);

	sub = new SpriteObj();
	sub->SetAll(*RESOURCE_MGR->GetTexture("graphics/minus.png"), { add->GetPos().x + add->GetSize().x, add->GetPos().y }, Origins::MC);
	uiObjList.push_back(sub);

	buy = new SpriteObj();
	buy->SetAll(*RESOURCE_MGR->GetTexture("graphics/buy.png"), { sub->GetPos().x + (sub->GetSize().x * 2), sub->GetPos().y }, Origins::MC);
	uiObjList.push_back(buy);

	edge = new SpriteObj();
	edge->SetAll(*RESOURCE_MGR->GetTexture("graphics/edge.png"), { sub->GetPos().x - (sub->GetSize().x * 2), sub->GetPos().y }, Origins::MC);
	uiObjList.push_back(edge);

	textBarricade = new TextObj();
	textBarricade->SetAll(font, to_string(buyBarricade), 60, Color::Black, 
		{ add->GetPos().x - add->GetSize().x * 2 + 80, barricade->GetPos().y - 30});
	uiObjList.push_back(textBarricade);

	price = new TextObj();
	price->SetAll(font, "PRICE : 40", 40, Color::Black, { edge->GetPos().x - 250, edge->GetPos().y - 50 });
	uiObjList.push_back(price);

	allPrice = new TextObj();
	allPrice->SetAll(font, "", 35, Color::Black, { edge->GetPos().x - 250, edge->GetPos().y + 20 });
	uiObjList.push_back(allPrice);

	cursor = new SpriteObj();
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
	buyBarricade = 0;
}

void UiETCShop::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->
		ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
	textGold->SetText(formatGold + to_string(Player::GetMoney()));

	allPrice->SetText(to_string(buyBarricade * barricadeval) + " GOLD");
	textBarricade->SetText(to_string(buyBarricade));


	if (cursor->GetPos().y >= add->GetPos().y - add->GetSize().y / 2 &&
		cursor->GetPos().y <= add->GetPos().y + add->GetSize().y / 2 &&
		cursor->GetPos().x >= add->GetPos().x - add->GetSize().x / 2 &&
		cursor->GetPos().x <= add->GetPos().x + add->GetSize().x / 2)
	{
		if (InputMgr::GetMouseButton(Mouse::Left))
		{
			add->SetTexture(*RESOURCE_MGR->GetTexture("graphics/addClick.png"));
		}
		if (InputMgr::GetMouseButtonUp(Mouse::Left))
		{
			add->SetTexture(*RESOURCE_MGR->GetTexture("graphics/add.png"));
			buyBarricade++;
		}
	}
	if (cursor->GetPos().y >= sub->GetPos().y - sub->GetSize().y / 2 &&
		cursor->GetPos().y <= sub->GetPos().y + sub->GetSize().y / 2 &&
		cursor->GetPos().x >= sub->GetPos().x - sub->GetSize().x / 2 &&
		cursor->GetPos().x <= sub->GetPos().x + sub->GetSize().x / 2)
	{
		if (InputMgr::GetMouseButton(Mouse::Left))
		{
			sub->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minusClick.png"));
		}
		if (InputMgr::GetMouseButtonUp(Mouse::Left))
		{
			sub->SetTexture(*RESOURCE_MGR->GetTexture("graphics/minus.png"));

			if (buyBarricade > 0)
			{
				buyBarricade--;
			}
		}
	}
	if (cursor->GetPos().y >= buy->GetPos().y - buy->GetSize().y / 2 &&
		cursor->GetPos().y <= buy->GetPos().y + buy->GetSize().y / 2 &&
		cursor->GetPos().x >= buy->GetPos().x - buy->GetSize().x / 2 &&
		cursor->GetPos().x <= buy->GetPos().x + buy->GetSize().x / 2)
	{
		if (InputMgr::GetMouseButton(Mouse::Left)&&(buyBarricade* barricadeval)<=Player::GetMoney())
		{
			buy->SetTexture(*RESOURCE_MGR->GetTexture("graphics/buyClick.png"));
		}
		if (InputMgr::GetMouseButtonUp(Mouse::Left) && (buyBarricade * barricadeval) <= Player::GetMoney())
		{
			buy->SetTexture(*RESOURCE_MGR->GetTexture("graphics/buy.png"));

			if (buyBarricade > 0)
			{
				Player::SetMoney(-1*(buyBarricade * barricadeval));
				SceneDev1::AddBaricount(buyBarricade);
				buyBarricade = 0;
				
			}
		}
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
