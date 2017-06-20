#include "Ship.h"

Ship::Ship( Point point, const unsigned int type, const bool rotation )
{
	hidden = 0;
	switch( type )
	{
	case 1:
		{
			point.isHited = false;
			points.push_back( point );
			break;
		}
	case 2:
		{
			points.push_back( point );
			if( rotation )
			{
				point.y++;
				points.push_back( point );
			}
			else
			{
				point.x++;
				points.push_back( point );
			}
			break;
		}
	case 3:
		{
			points.push_back( point );
			if( rotation )
			{
				for( int i = 0; i < 2; i++)
				{
					point.y++;
					points.push_back( point );
				}
			}
			else
			{
				for( int i = 0; i < 2; i++)
				{
					point.x++;
					points.push_back( point );
				}
			}
			break;
		}

	case 4:
		{
			points.push_back( point );
			if( rotation )
			{
				for( int i = 0; i < 3; i++)
				{
					point.y++;
					points.push_back( point );
				}
			}
			else
			{
				for( int i = 0; i < 3; i++)
				{
					point.x++;
					points.push_back( point );
				}
			}
			break;
		}

	default:
		{
			//exit(0);
			break;
		}
	}
}

bool Ship::operator ==( const Ship& ship )
{
	const int shipSaveFields = 9;
	Point saveField;
	int compareSize = 0;
	if( this->points.size() > ship.points.size() )
		compareSize = ship.points.size();
	else
		compareSize = this->points.size();
	for( int i = 0; i < this->points.size(); i++ )
	{
		for( int k = 0; k < ship.points.size(); k++ )
		{
			
			if( this->points[i] == ship.points[k] )
				return true;
			else
				return false;

		}
	}
}

bool Ship::isSunk()
{
	int counter = 0;
	for( int i = 0; i < points.size(); i ++ )
	{
		if(this->points[i].isHited)
			counter++;
	}
	if( counter == points.size())
		return true;
	else
		return false;
}