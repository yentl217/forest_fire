#ifndef TOOLS_CPP
#define TOOLS_CPP

#include <iostream>
#include "coord.h"
using namespace std;

void new_searches(coord* coords_to_search, coord central_coord, int length, int width)
{
	int x_plus = central_coord.get_x()+1;
	if (x_plus == length) x_plus = 0;
	int x_minus = central_coord.get_x()-1;
	if (x_minus == -1) x_minus = length-1;
	int y_plus = central_coord.get_y()+1;
	if (y_plus == width) y_plus = 0;
	int y_minus = central_coord.get_y()-1;
	if (y_minus == -1) y_minus = width-1;
	
	coords_to_search[0]=coord(x_plus,central_coord.get_y());
	coords_to_search[1]=coord(x_minus,central_coord.get_y());
	coords_to_search[2]=coord(central_coord.get_x(),y_plus);
	coords_to_search[3]=coord(central_coord.get_x(),y_minus);
}

#endif
