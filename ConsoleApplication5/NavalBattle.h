#include <ctime>
#include "Ship.h"
#include "BaseApplication.h"


class NavalBattle : public BaseAplication
{
public:
	void start();
	
private:
	vector<Ship> ships_;
	void processShot( int x, int y);
	void shipGen();
	void askShotTarget();
	void aiShot();
    void setScreenBuf();
	void checkForWin();
};