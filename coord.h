#ifndef COORD_H
#define COORD_H

#include <iostream>
using namespace std;

class coord
{
	int x;
	int y;
	public:
		coord(int int_x,int int_y)
		{
			x = int_x;
			y = int_y;
		}
		coord()
		{
			x = 0;
			y = 0;
		}
		int get_x()
		{
			return x;
		}
		int get_y()
		{
			return y;
		}
		void set_x(int new_x)
		{
			x = new_x;
		}
		void set_y(int new_y)
		{
			y = new_y;
		}
		void set_coord(int new_x, int new_y)
		{
			x = new_x;
			y = new_y;
		}
		bool operator==(coord comp_coord)
		{
			if (x == comp_coord.x && y == comp_coord.y) return true;
			else return false;
		}
};	

#endif
