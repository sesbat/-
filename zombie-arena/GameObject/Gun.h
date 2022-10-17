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


class Gun :public Singleton<Gun>
{
protected:
	struct firemode {
		bool AUTO;
		bool BURST;
		bool MANUAL;
		enum class Gunmode {
			AUTO,
			BURST,
			MANUAL,
		};
		Gunmode CUR;
		int firmodetemp;
	};
	struct gunstat {
		int currentammo;
		int maxammo;
		int magcount;
		bool unlocked;
		float relaodtimer;
		firemode mode;
	};

	TYPE currentgun;
	map<TYPE, gunstat*> gun;

public:
	Gun();
	~Gun();

	void Change(int a) {
		if (gun[(TYPE)a]->unlocked)
			currentgun = (TYPE)a;
	}
	int PrintCurrentammo() {
		return gun[currentgun]->currentammo;
	}
	int PrintMagCount() {
		return gun[currentgun]->magcount;
	}

	firemode::Gunmode PrintCurrentMode() {
		return gun[currentgun]->mode.CUR;
	}
	void shoot() {
		gun[currentgun]->currentammo--;
		
	}
	void Reload() {
		gun[currentgun]->magcount--;
		gun[currentgun]->currentammo= gun[currentgun]->maxammo;		
	}
	void UnlockGun(int type) {
		gun[(TYPE)type]->unlocked = true;
	}

	float PrintReloadTime() {
		return gun[currentgun]->relaodtimer;
	}

	void BuyMag(TYPE type, int a) {
		gun[type]->magcount += a;
	}

	void SetFireMode() {
		
		int temp = gun[currentgun]->mode.firmodetemp;
		temp++;
		temp = temp % 3;
		gun[currentgun]->mode.firmodetemp = temp;
		switch (temp) {
		case 0:
			if (gun[currentgun]->mode.AUTO) {
				gun[currentgun]->mode.CUR = (firemode::Gunmode)temp;
			}
			else {
				gun[currentgun]->mode.firmodetemp = temp;
				
			}
			break;
		case 1:
			if (gun[currentgun]->mode.BURST) {
				gun[currentgun]->mode.CUR = (firemode::Gunmode)temp;
			}
			else {
				gun[currentgun]->mode.firmodetemp = temp;

			}
			break;
		case 2:
			if (gun[currentgun]->mode.MANUAL) {
				gun[currentgun]->mode.CUR = (firemode::Gunmode)temp;
			}
			else {
				gun[currentgun]->mode.firmodetemp = temp;

			}
			break;
		}
	}

	int PrintCurrent() { return (int)currentgun; }
	
};

#define GUN (Gun::GetInstance())