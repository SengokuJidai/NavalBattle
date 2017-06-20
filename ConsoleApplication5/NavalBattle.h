#include <Windows.h>
#include <iostream>
#include <ctime>
#include "Ship.h"
using namespace std;

class NavalBattle
{
private:
	const unsigned int sizeX_;
	const unsigned int sizeY_;
	char* navalBuffer_;
	vector<Ship> ships_;
	void setChar( unsigned int x, unsigned int y, char c);
	char getChar( unsigned int x, unsigned int y);
	void processShot( int x, int y);
	void setTable();
	void shipGen();
	void printBuffer();
	void askShotTarget();
	void aiShot();
	

public:
	NavalBattle( unsigned int x = 40, unsigned int y = 20 );
	void start();

	~NavalBattle();
};