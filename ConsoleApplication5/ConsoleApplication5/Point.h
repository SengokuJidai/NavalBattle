#pragma once

#include <vector>

struct Point
{
	unsigned int x;
	unsigned int y;
	bool isHited;
	Point();
	bool operator ==( const Point& point );
	bool operator !=( const Point& point );
};