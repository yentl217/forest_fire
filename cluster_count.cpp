#ifndef CLUSTER_COUNT_CPP
#define CLUSTER_COUNT_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include "coord.h"
using namespace std;

void search_loop(vector<coord>& new_starts, coord start,vector<int *>& trees, int length, int width)
{
	int x_plus = start.get_x()+1;
	if (x_plus == length) x_plus = 0;
	int x_minus = start.get_x()-1;
	if (x_minus == -1) x_minus = length-1;
	int y_plus = start.get_y()+1;
	if (y_plus == width) y_plus = 0;
	int y_minus = start.get_y()-1;
	if (y_minus == -1) y_minus = width-1;
	
	coord current_searches[4] = {coord(x_plus,start.get_y()),coord(x_minus,start.get_y()),coord(start.get_x(),y_plus),coord(start.get_x(),y_minus)};
	
	for(int i = 0; i<4; i++)
	{
		int count=0;
		if (trees[current_searches[i].get_y()][current_searches[i].get_x()] == 1)
		{
			while (count <new_starts.size())
			{
				if(new_starts[count] == current_searches[i]) break;
				count++;
			}
			if (count == new_starts.size()) new_starts.push_back(current_searches[i]);
		}
	}
}	

void cluster_count(vector<int *> matrix,int length, int width)
{
	//Generate array of positions of burning trees
	vector<coord> positions;
	for (int y=0;y<width;y++)
	{
		for (int x = 0; x<length; x++)
		{
			if (matrix[y][x] == 1)
			{
				positions.push_back(coord(x,y));
			}
		}
	}
	while(positions.size() != 0)
	{
		//vector containing positions around which one searches to expand the cluster
		vector<coord> new_starts;
		//vector containing positions already identified as part of the cluster
		vector<coord> cluster;
		
		cluster.push_back(positions[0]);
		search_loop(new_starts,positions[0],matrix,length,width);
		
		//set searched position to 0 to prevent research.
		matrix[positions[0].get_y()][positions[0].get_x()] = 0;
		//erase from positions matrix to prevent re-search
		positions.erase(positions.begin());
		
		//continue until edge of cluster has been found
		while(new_starts.size() !=0)
		{
			search_loop(new_starts,new_starts[0],matrix,length,width);
			matrix[new_starts[0].get_y()][new_starts[0].get_x()] = 0;
			cluster.push_back(new_starts[0]);
			//erase from positions matrix
			for (int i =0; i<positions.size();i++)
			{
				if(positions[i] == new_starts[0]) positions.erase(positions.begin()+i);
			}
			new_starts.erase(new_starts.begin());		
		}
		cout << cluster.size() << endl;
	}				
		
}				
#endif


	
