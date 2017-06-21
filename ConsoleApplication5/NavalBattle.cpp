#include <string>
#include "NavalBattle.h"


void NavalBattle::start()
{
	setScreenBuf();
	printBuffer();
	while(true)
	{
		askShotTarget();
		aiShot();
		system("cls");
		printBuffer();
		checkForWin();
	}
}



void NavalBattle::setScreenBuf()
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
	srand( time(0) );
	vector<Point> taboo;
	const int nShips = 20;
	unsigned int type = 4;
	int rotation = 0;
	Point start;
	Point startEnemy;
	
	int tableMaxX = 13;
	const int tableMaxY = 13;
	for( int i = 0; i < nShips; i ++ )
	{
		if( i >= nShips/2 )
		{
			if( i == 10 )
				type = 4;
			start.x = 24 + rand()%30;
			tableMaxX = 33;
		}
		else
			start.x = 4 + rand()%10;
		start.y = 4 + rand()%10;

		rotation = rand()%2;

		if( i == 1 || i == 3 || i == 6 || i == 11 || i == 13 || i == 16)
			type--;
		ships_.push_back(Ship(start, type, rotation ));
		if( i >= nShips/2 )
		{
			ships_[i].hidden = true;
		}
		for(int k = 0; k < ships_[i].points.size(); k++)
		{
			while( ships_[i].points[k].x > tableMaxX )
			{
				for(int j = 0; j < ships_[i].points.size(); j++)
				{
					ships_[i].points[j].x--;
				}
			}
			while( ships_[i].points[k].y > tableMaxY )
			{
				for(int j = 0; j < ships_[i].points.size(); j++)
				{
					ships_[i].points[j].y--;
				}
			}
		}
		if( i != 0 )
		{
			for( int k = 0; k < ships_.size()-1; k++ )
			{
				if( ships_[i] == ships_[k] )
				{
					ships_.pop_back();
					if( i == 1 || i == 3 || i == 6 || i == 11 || i == 13 || i == 16 )
					{
						type++;
					}
					i--;
				}
			}
		}
	}
	
	for(int i = 0; i < ships_.size(); i++)
	{
		for(int k = 0; k < ships_[i].points.size(); k++)
		{
			if(ships_[i].hidden == false )
				setChar(ships_[i].points[k].x, ships_[i].points[k].y, 178);
		}
	}
}

void NavalBattle::checkForWin()
{
	const int nShips = 20;
	int sunkenShipCounter = 0;
	int sunkenEnemyShipCounter = 0;
	for( int i = 0; i < nShips; i ++ )
	{
		if( ships_[i].isSunk() == true )
		{
			if( i < nShips/2 )
				sunkenShipCounter++;
			else
				sunkenEnemyShipCounter++;
		}
	}
	if( sunkenEnemyShipCounter == 10 )
	{
		system("cls");
		cout<<"You win"<<endl;
		exit(0);
	}
	if( sunkenShipCounter == 10 )
	{
		for( int i = 10; i < nShips; i ++ )
		{
			ships_[i].hidden = false;
		}
		for(int i = 0; i < ships_.size(); i++)
		{
			for(int k = 0; k < ships_[i].points.size(); k++)
			{
				if(ships_[i].hidden == false )
					setChar(ships_[i].points[k].x, ships_[i].points[k].y, 178);
			}
		}
		system("cls");
		printBuffer();
		//exit(0);
	}
}

void NavalBattle::askShotTarget()
{
	int y = 0;
	int x = 0;
	cout<<endl<<"Your turn. Enter shot coordinate. First - Symbol coordinate, then number. Example: A2"<<endl;
	string input;
	cin>>input;
	const char* a = &input[1];
	y = atoi(a);
	if( static_cast<int>(input[0]) > 74 )
		x = static_cast<int>(input[0])-96;
	else
		x = static_cast<int>(input[0])-64;
	while( input.size() < 2 || input.size() > 3 )
	{
		cout<<endl<<"Wrong input. Try again"<<endl;
		cin>>input;
		const char* stringNumber = &input[1];
		y = atoi(stringNumber);
		if( static_cast<int>(input[0]) > 74 )
			x = static_cast<int>(input[0])-96;
		else
			x = static_cast<int>(input[0])-64;
	}
	while( y < 1 || y > 10 || x < 1 || x > 10 )
	{
		cout<<endl<<"Wrong input. Try again"<<endl;
		cin>>input;
		const char* a = &input[1];
		y = atoi(a);
		if( static_cast<int>(input[0]) > 74 )
			x = static_cast<int>(input[0])-96;
		else
			x = static_cast<int>(input[0])-64;
	}
	while( static_cast<int>(input[0]) < 65 || static_cast<int>(input[0]) > 74 && static_cast<int>(input[0]) < 97 || static_cast<int>(input[0]) > 106 )
	{
		cout<<endl<<"Wrong input. Try again"<<endl;
		cin>>input;
		const char* a = &input[1];
		y = atoi(a);
		if( (int)input[0] > 74 )
			x = (int)input[0]-96;
		else
			x = (int)input[0]-64;
	}
	
	if(x > 10)
		x = 10;
	if(y > 10)
		y = 10;
	if(x < 1)
		x = 1;
	if(y < 1)
		y = 1;
	char sunkenShipSymbol =  static_cast<char>(176);
	if( getChar( x+23,y+3) == '*' || getChar( x+23,y+3) == 'X' || getChar( x+23,y+3) == sunkenShipSymbol )
	{
		cout<<"Already shooted"<<endl;
		system("pause");
	}
	processShot( x+20, y );
}

void NavalBattle::aiShot()
{
	int x = 1 + rand()%10;
	int y = 1 + rand()%10;
	if(x > 10)
		x = 10;
	if(y > 10)
		y = 10;
	if(x < 1)
		x = 1;
	if(y < 1)
		y = 1;
	char a =  static_cast<char>(178);
	if( getChar( x+3,y+3) == a || getChar( x+3,y+3) == '.' )
		processShot( x, y ); 
	else
	{
		aiShot(); // Вечный цикл если боту некуда больше стрелять. Переделать.
	}
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

