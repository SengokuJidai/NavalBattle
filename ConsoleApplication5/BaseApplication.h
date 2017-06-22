#include <Windows.h>
#include <iostream>
using namespace std;

class BaseAplication
{
public:
	BaseAplication(const unsigned int x = 40, const unsigned int y = 15);
	void printBuffer();
	void setChar( unsigned int x, unsigned int y, char c);
	char getChar( unsigned int x, unsigned int y);
	virtual void start() = 0;
	virtual ~BaseAplication();
private:
	const unsigned int sizeX_;
	const unsigned int sizeY_;
	char* screenBuffer_;
};