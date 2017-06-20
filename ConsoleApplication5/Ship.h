
#include "Point.h"

class Ship
{
public:
	std::vector<Point> points;
	bool hidden;
	Ship( Point coord, const unsigned int type, const bool rotation );
	bool operator ==( const Ship& ship );
	bool operator !=( const Ship& ship );
	bool isSunk();
};
