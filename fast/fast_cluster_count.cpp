#ifndef FAST_CLUSTER_COUNT_CPP
#define FAST_CLUSTER_COUNT_CPP

#include <iostream>
#include "tools.cpp"
#include "coord.h"
#include "vector"
using namespace std;

void search_loop(vector<coord>& new_starts, coord start,int **trees, int length, int width)
{
	coord current_searches[4];
	new_searches(current_searches,start,length,width);
	
	for(int i = 0; i<4; i++)
	{
		int count=0;
		if (trees[current_searches[i].get_y()][current_searches[i].get_x()] == 2)
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

void fast_count(int **forest, int length, int width, coord init,vector<coord> &cluster)
{
	vector<coord> new_starts;
	
	cluster.push_back(init);
	forest[init.get_x()][init.get_y()] = 1;
	
	search_loop(new_starts,init,forest,length,width);
	while(new_starts.size() !=0 )
	{
		search_loop(new_starts,new_starts[0],forest,length,width);
		forest[new_starts[0].get_y()][new_starts[0].get_x()] = 1;
		cluster.push_back(new_starts[0]);
		new_starts.erase(new_starts.begin());
	}
}

#endif
