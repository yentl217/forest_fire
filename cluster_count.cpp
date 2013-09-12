#ifndef CLUSTER_COUNT_CPP
#define CLUSTER_COUNT_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include "coord.h"
using namespace std;

void search_loop(vector<coord>& new_starts, coord start, int &cluster_size, vector<int *>& trees, int length, int width)
//TODO:condense!
{
	int i =0;
	if (start.get_x() != length-1)
	{
		if (trees[start.get_y()][start.get_x()+1] == 1) 
		{
			while (i<new_starts.size())
			{
				if(new_starts[i] == coord(start.get_x()+1,start.get_y())) break;
				i++;
			}
			if (i == new_starts.size())
			{
				new_starts.push_back(coord(start.get_x()+1,start.get_y()));
				cluster_size++;
			}
		}
	}
	
	if (start.get_x() != 0)
	{
		if (trees[start.get_y()][start.get_x()-1] == 1) 
		{
			i = 0;
			while (i<new_starts.size())
			{
				if(new_starts[i] == coord(start.get_x()-1,start.get_y())) break;
				i++;
			}
			if (i == new_starts.size())
			{
				new_starts.push_back(coord(start.get_x()-1,start.get_y()));
				cluster_size++;
			}
		}
	}
	
	if (start.get_y() != width-1)
	{
		if (trees[start.get_y()+1][start.get_x()] == 1) 
		{
			i = 0;
			while (i<new_starts.size())
			{
				if(new_starts[i] == coord(start.get_x(),start.get_y()+1)) break;
				i++;
			}
			if (i == new_starts.size())
			{
				new_starts.push_back(coord(start.get_x(),start.get_y()+1));
				cluster_size++;
			}
		}
	}
	
	if (start.get_y() != 0)
	{
		if (trees[start.get_y()-1][start.get_x()] == 1) 
		{
			i = 0;
			while (i<new_starts.size())
			{
				if(new_starts[i] == coord(start.get_x(),start.get_y()-1)) break;
				i++;
			}
			if (i == new_starts.size())
			{
				new_starts.push_back(coord(start.get_x(),start.get_y()-1));
				cluster_size++;
			}
		}
	}
}
	

//TODO: how to incorporate periodic boundaries?
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
		vector<coord> new_starts;
		int cluster_size = 1;
		search_loop(new_starts,positions[0],cluster_size,matrix,length,width);
		matrix[positions[0].get_y()][positions[0].get_x()] = 0;
		positions.erase(positions.begin());
		while(new_starts.size() !=0)
		{
			search_loop(new_starts,new_starts[0],cluster_size,matrix,length,width);
			matrix[new_starts[0].get_y()][new_starts[0].get_x()] = 0;
			//erase from positions matrix
			for (int i =0; i<positions.size();i++)
			{
				if(positions[i] == new_starts[0]) positions.erase(positions.begin()+i);
			}
			new_starts.erase(new_starts.begin());		
		}
		cout << cluster_size << endl;
	}				
		
}				
#endif


	
