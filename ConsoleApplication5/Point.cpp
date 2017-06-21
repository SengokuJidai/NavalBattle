#include "Point.h"

Point::Point() : x(0), y(0), isHited(false)
{
}

bool Point::operator ==( const Point& point )
{
	if( this->x == point.x && this->y == point.y )
		return true;
	else
		return false;
}

bool Point::operator !=( const Point& point )
{
	if( *this == point )
		return false;
	else
		return true;
}
