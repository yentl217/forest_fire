#ifndef COORD_H
#define COORD_H

#include <iostream>
using namespace std;

//object defining each cell of the forest fire model
class coord
{
	int x;
	int y;
	public:
		coord(int int_x,int int_y) //creates a cell at co-ordinates int_x and int_y
		{
			x = int_x;
			y = int_y;
		}
		coord()
		{
			x = 0; //creates a default cell at the (0,0) co-ordinate
			y = 0;
		}
		int get_x() //fetches x co-ordinate of cell
		{
			return x;
		}
		int get_y() //fetches y co-ordinate of cell
		{
			return y;
		}
		void set_x(int new_x) //resets x co-ordinate of cell
		{
			x = new_x;
		}
		void set_y(int new_y) //resets y co-ordinate of cell
		{
			y = new_y;
		}
		void set_coord(int new_x, int new_y) //resets x and y co-ordinate of cell
		{
			x = new_x;
			y = new_y;
		}
		bool operator==(coord comp_coord) // define == operator to compare whether two cells are the same (i.e. has the same x and y co-ordinates)
		{
			if (x == comp_coord.x && y == comp_coord.y) return true;
			else return false;
		}
};	

#endif
