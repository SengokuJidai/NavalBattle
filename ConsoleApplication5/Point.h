#include <vector>

struct Point
{
	unsigned int x;
	unsigned int y;
	bool isHited;
	Point();
	bool operator ==( const Point& shot );
	bool operator !=( const Point& shot );
};