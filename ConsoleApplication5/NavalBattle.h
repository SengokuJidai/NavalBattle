#pragma once

#include <ctime>
#include "Ship.h"
#include "BaseApplication.h"


class NavalBattle : public BaseAplication
{
public:
	NavalBattle();
	
private:
	vector<Ship> ships_;
	void cycledScreen();
	void processShot( int x, int y);
	void shipGen();
	void askShotTarget();
	void aiShot();
    void setStartBuf();
	void checkForWin();
};