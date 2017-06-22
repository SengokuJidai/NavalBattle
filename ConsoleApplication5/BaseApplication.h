#pragma once

#include <Windows.h>
#include <iostream>
using namespace std;

class BaseAplication
{
public:
	BaseAplication(const unsigned int x = 40, const unsigned int y = 15);
	void setChar( unsigned int x, unsigned int y, char c);
	char getChar( unsigned int x, unsigned int y);
	void printBuffer();
	void start();
	virtual void cycledScreen() = 0;
	virtual ~BaseAplication();
private:

	const unsigned int sizeX_;
	const unsigned int sizeY_;
	char* screenBuffer_;
};