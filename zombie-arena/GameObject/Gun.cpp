#include "Gun.h"

Gun::Gun()
{
	gunstat* pistol = new gunstat();
	pistol->currentammo = 8;
	pistol->maxammo = 8;
	pistol->magcount = 10;
	pistol->unlocked = true;
	pistol->relaodtimer = 0.5f;
	pistol->mode.AUTO = false;
	pistol->mode.BURST = false;
	pistol->mode.MANUAL = true;
	pistol->mode.CUR = firemode::Gunmode::MANUAL;
	pistol->mode.firmodetemp = 2;
	pistol->damage = 20;
	gun.insert({ TYPE::PISTOL,pistol });

	gunstat* rifle = new gunstat();
	rifle->currentammo = 30;
	rifle->maxammo = 30;
	rifle->magcount = 0;
	rifle->unlocked = false;
	rifle->relaodtimer = 3;
	rifle->mode.AUTO = true;
	rifle->mode.BURST = true;
	rifle->mode.MANUAL = true;
	rifle->mode.CUR = firemode::Gunmode::MANUAL;
	rifle->damage = 30;
	rifle->mode.firmodetemp = 2;

	gun.insert({ TYPE::RIFLE,rifle });

	gunstat* shotgun = new gunstat();
	shotgun->currentammo = 10;
	shotgun->maxammo = 5;
	shotgun->magcount = 0;
	shotgun->unlocked = false;
	shotgun->mode.AUTO = false;
	shotgun->mode.BURST = false;
	shotgun->mode.MANUAL = true;
	shotgun->mode.CUR = firemode::Gunmode::MANUAL;
	shotgun->mode.firmodetemp = 2;
	shotgun->relaodtimer = 1;
	shotgun->damage = 20;
	gun.insert({ TYPE::SHOTGUN,shotgun });

	currentgun = TYPE::PISTOL;

}

Gun::~Gun()
{
	for (auto v : gun) {
		delete v.second;
	}
	gun.clear();
}

void Gun::Change(int a)
{
	if (gun[(TYPE)a]->unlocked)
		currentgun = (TYPE)a;
}

string Gun::PrintStringCurrentMode()
{
	switch (gun[currentgun]->mode.CUR) {
	case firemode::Gunmode::AUTO:
		return "Auto";
	case firemode::Gunmode::BURST:
		return "Burst";
	case firemode::Gunmode::MANUAL:
		return "Manual";
	}
}

void Gun::Reload()
{
	gun[currentgun]->magcount--;
	gun[currentgun]->currentammo = gun[currentgun]->maxammo;
}

void Gun::SetFireMode()
{


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
