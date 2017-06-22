#include "BaseApplication.h"

BaseAplication::BaseAplication( const unsigned int x, const unsigned int y ) : sizeX_(x), sizeY_(y)
{
	/*
	HANDLE mConsole;
	HANDLE mConsoleIn;
	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);*/

	screenBuffer_ = new char[(sizeX_+1)*(sizeY_+1)];
	for( int i = 0; i < (sizeX_+1)*(sizeY_+1); i++ )
	{
		screenBuffer_[i] = ' ';
	}
}

void BaseAplication::setChar( unsigned int x, unsigned int y, char c)
{
	screenBuffer_[x + (sizeX_)*(y-1)] = c;
}

char BaseAplication::getChar( unsigned int x, unsigned int y)
{
	return screenBuffer_[x + (sizeX_)*(y-1)];
}

void BaseAplication::start()
{
	while(true)
	{
		cycledScreen();
	}
}

void BaseAplication::printBuffer()
{
	system("cls");
	for( int i = 0; i < (sizeX_+1)*(sizeY_+1); i++ )
	{
		if( i % sizeX_ != 0 )
		{
			cout<<screenBuffer_[i];
		}
		else if( i != 0 )
		{
			cout<<screenBuffer_[i]<<endl;
		}
	}
	cout<<endl;
}

BaseAplication::~BaseAplication()
{
	delete[] screenBuffer_;
}