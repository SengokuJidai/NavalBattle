#include "NavalBattle.h"

NavalBattle::NavalBattle( unsigned int x, unsigned int y ) : sizeX_(x), sizeY_(y)
{
	srand( time(0) );
	HANDLE mConsole;
	HANDLE mConsoleIn;
	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);

	navalBuffer_ = new char[(sizeX_+1)*(sizeY_+1)];
	for( int i = 0; i < (sizeX_+1)*(sizeY_+1); i++ )
	{
		navalBuffer_[i] = ' ';
	}
}

void NavalBattle::start()
{
	setTable();
	printBuffer();
	while(true)
	{
		askShotTarget();
		aiShot();
		system("cls");
		printBuffer();
	}


}

void NavalBattle::setChar( unsigned int x, unsigned int y, char c)
{
	navalBuffer_[x + (sizeX_)*(y-1)] = c;
}

char NavalBattle::getChar( unsigned int x, unsigned int y)
{
	return navalBuffer_[x + (sizeX_)*(y-1)];
}

void NavalBattle::printBuffer()
{
	for( int i = 0; i < (sizeX_+1)*(sizeY_+1); i++ )
	{
		if( i % sizeX_ != 0 )
		{
			cout<<navalBuffer_[i];
		}
		else if( i != 0 )
		{
			cout<<navalBuffer_[i]<<endl;
		}
	}
}

void NavalBattle::setTable()
{
	const int x = 3, y = 3;
	const int tableSize = 12;

	for( int i = x; i < x+tableSize; i++ )
	{
		for( int k = y; k < y+tableSize; k++ )
		{
			if( i == x && k > y+1 )
			{
				setChar(i-1,k-1,k+44);
				setChar(i+19,k-1,k+44);
				if( k == y+11 )
				{
					setChar(i-1,k-1,'0');
					setChar(i-2,k-1,'1');
					setChar(i+19,k-1,'0');
					setChar(i+18,k-1,'1');
				}
			}

			if( k == x && i > y+1 )
			{
				setChar(i-1,x-1,i+60);
				setChar(i+19,x-1,i+60);
			}

			if( i == x || i == x +tableSize-1 || k == y || k == y +tableSize-1 )
			{
				setChar(i,k,'#');
				setChar(i+20,k,'#');
			}
			else
			{
				setChar(i,k,'.');
				setChar(i+20,k,'.');
			}
		}
	}
	shipGen();
}

void NavalBattle::shipGen()
{

	const int nShips = 10;
	unsigned int type = 4;
	Point start;
	start.x = 4;
	start.y = 4;
	int rotation = 0;
	ships_.push_back(Ship(start, type, rotation ));
	start.x = 24;
	start.y = 4;
	ships_.push_back(Ship(start, type, rotation ));
	ships_[1].hidden = 1;
	type = 3;
	start.x = 26;
	start.y = 10;
	ships_.push_back(Ship(start, type, rotation ));
	ships_[2].hidden = 1;


	/*
	for( int i = 0; i < nShips; i ++ )
	{
	int rotation = rand()%2;
	start.x = 4 + rand()%10;
	start.y = 4 + rand()%10;
	if( i == 1 || i == 3 || i == 6 )
	type--;
	ships_.push_back(Ship(start, type, rotation ));
	if( i > 0 )
	{
	if( ships_[i] == ships_[i-1] )
	{
	for( int k = 0; k < ships_[i].points.size(); k++ )
	{
	ships_[i].points[k].x+2;
	}
	}
	}
	}*/

	for(int i = 0; i < ships_.size(); i++)
	{
		for(int k = 0; k < ships_[i].points.size(); k++)
		{
			if(ships_[i].hidden == false )
				setChar(ships_[i].points[k].x, ships_[i].points[k].y, 178);
		}
	}
}

void NavalBattle::askShotTarget()
{
	int y = 0;
	int x = 0;
	cout<<endl<<"Your turn. Enter shot coordinate"<<endl;
	cin>>x>>y;
	cout<< x << y << endl;
	if(x > 10)
		x = 10;
	if(y > 10)
		y = 10;
	if(x < 1)
		x = 1;
	if(y < 1)
		y = 1;
	processShot( x+20, y );
}

void NavalBattle::aiShot()
{
	int x = 1 + rand()%10;
	int y = 1 + rand()%10;
	processShot( x, y );
}

void NavalBattle::processShot( int x, int y)
{
	bool hitting = false;
	for(int i = 0; i < ships_.size(); i++)
	{
		for(int k = 0; k < ships_[i].points.size(); k++)
		{
			if( ships_[i].points[k].x == x+3 && ships_[i].points[k].y == y+3 )
			{
				hitting = true;
				ships_[i].points[k].isHited = true;
			}
		}
	}
	if( hitting == true )
		setChar(x+3, y+3, 'X');
	else
		setChar(x+3, y+3, '*');

	char check;
	for(int i = 0; i < ships_.size(); i++)
	{
		if(ships_[i].isSunk() == true)
		{
			for( int k = 0; k < ships_[i].points.size(); k++ )
			{
				setChar(ships_[i].points[k].x, ships_[i].points[k].y, 176);

				check = getChar(ships_[i].points[k].x+1, ships_[i].points[k].y+1);
				if( check == '.' )
					setChar(ships_[i].points[k].x+1, ships_[i].points[k].y+1, '*');
				check = getChar(ships_[i].points[k].x+1, ships_[i].points[k].y);
				if( check == '.' )
					setChar(ships_[i].points[k].x+1, ships_[i].points[k].y, '*');
				check = getChar(ships_[i].points[k].x, ships_[i].points[k].y+1);
				if( check == '.'  )
					setChar(ships_[i].points[k].x, ships_[i].points[k].y+1, '*');
				check = getChar(ships_[i].points[k].x+1, ships_[i].points[k].y-1);
				if( check == '.' )
					setChar(ships_[i].points[k].x+1, ships_[i].points[k].y-1, '*');
				check = getChar(ships_[i].points[k].x-1, ships_[i].points[k].y+1);
				if( check == '.' )
					setChar(ships_[i].points[k].x-1, ships_[i].points[k].y+1, '*');
				check = getChar(ships_[i].points[k].x-1, ships_[i].points[k].y);
				if( check == '.' )
					setChar(ships_[i].points[k].x-1, ships_[i].points[k].y, '*');
				check = getChar(ships_[i].points[k].x, ships_[i].points[k].y-1);
				if( check == '.' )
					setChar(ships_[i].points[k].x, ships_[i].points[k].y-1, '*');
				check = getChar(ships_[i].points[k].x-1, ships_[i].points[k].y-1);
				if( check == '.' )
					setChar(ships_[i].points[k].x-1, ships_[i].points[k].y-1, '*');
			}
		}
	}
}

NavalBattle::~NavalBattle()
{
	delete[] navalBuffer_;
}