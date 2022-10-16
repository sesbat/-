#pragma once

#include <map>
#include "../3rd/Singleton.h"
#include <iostream>

using namespace std;

enum class TYPE
{
	PISTOL,
	RIFLE,
	SHOTGUN,
};

class Gun:public Singleton<Gun>
{
protected:
	struct gunstat {
		int currentammo;
		int maxammo;
		int magcount;
		bool unlocked;
	};

	TYPE currentgun;
	map<TYPE, gunstat*> gun;

public:
	Gun();
	~Gun();

	void Test() {
		cout<<gun[currentgun]->currentammo<<endl;
	}
};

#define GUN (Gun::GetInstance())