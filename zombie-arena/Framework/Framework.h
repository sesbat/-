#pragma once
#include "../3rd/Singleton.h"
#include <SFML/Graphics.hpp>
#include "../GameObject/Gun.h"
using namespace sf;

class Gun;
class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2i windowSize;

	// TimeMgr
	Clock clock;
	Time deltaTime;
	float timeScale;
	Gun gun;
public:
	Framework();
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;
	const Vector2i& GetWindowSize() const;
	RenderWindow& GetWindow();

	bool Init(int width, int height);
	bool Do();
};

#define FRAMEWORK (Framework::GetInstance())