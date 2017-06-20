#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
	isHited = false;
}

bool Point::operator ==( const Point& shot )
{
	if( this->x == shot.x && this->y == shot.y )
		return true;
	else
		return false;
}

bool Point::operator !=( const Point& shot )
{
	if( this->x != shot.x || this->y != shot.y )
		return true;
	else
		return false;
}
