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

bool Ship::operator ==( const Ship& ship )
{
	for( int i = 0; i < this->points.size(); i++ )
	{
		for( int k = 0; k < ship.points.size(); k++ )
		{
			if( this->points[i] == ship.points[k] )
				return true;
			else if( this->points[i].x == ship.points[k].x+1 && this->points[i].y == ship.points[k].y+1 )
				return true;
			else if( this->points[i].x == ship.points[k].x-1 && this->points[i].y == ship.points[k].y-1 )
				return true;
			else if( this->points[i].x == ship.points[k].x+1 && this->points[i].y == ship.points[k].y-1 )
				return true;
			else if( this->points[i].x == ship.points[k].x-1 && this->points[i].y == ship.points[k].y+1 )
				return true;
			else if( this->points[i].x == ship.points[k].x-1 && this->points[i].y == ship.points[k].y )
				return true;
			else if( this->points[i].x == ship.points[k].x+1 && this->points[i].y == ship.points[k].y )
				return true;
			else if( this->points[i].x == ship.points[k].x && this->points[i].y == ship.points[k].y-1 )
				return true;
			else if( this->points[i].x == ship.points[k].x && this->points[i].y == ship.points[k].y+1 )
				return true;
		}
	}
	return false;
}

bool Ship::operator !=( const Ship& ship )
{
	if( *this == ship)
		return false;
	else
		return true;
}