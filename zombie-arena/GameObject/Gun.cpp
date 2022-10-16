#include "Gun.h"

Gun::Gun()
{
	gunstat* pistol = new gunstat();
	pistol->currentammo=8;
	pistol->maxammo=8;
	pistol->magcount = 10;
	pistol->unlocked = true;

	gun.insert({ TYPE::PISTOL,pistol });

	gunstat* rifle = new gunstat();
	rifle->currentammo = 0;
	rifle->maxammo = 30;
	rifle->magcount = 0;
	rifle->unlocked = false;

	gun.insert({ TYPE::RIFLE,rifle });

	gunstat* shotgun=new gunstat();
	shotgun->currentammo = 0;
	shotgun->maxammo = 5;
	shotgun->magcount = 0;
	shotgun->unlocked = false;

	gun.insert({ TYPE::RIFLE,shotgun });

	currentgun = TYPE::PISTOL;
	
}

Gun::~Gun()
{
	for (auto v : gun) {
		delete v.second;
	}
	gun.clear();	
}
