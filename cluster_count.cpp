#ifndef CLUSTER_COUNT_CPP
#define CLUSTER_COUNT_CPP

#include <iostream>
#include <vector>
#include "coord.h"
#include "tools.cpp"
using namespace std;

void search_loop(vector<coord>& new_starts, coord start,vector<int *>& trees, int length, int width)
{
	coord current_searches[4];
	new_searches(current_searches,start,length,width);
	
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

void cluster_count(vector<int *> matrix,int length, int width,vector<coord >& positions, ofstream& clusters)
{
	while(positions.size() != 0)
	{
		//vector containing positions around which one searches to expand the cluster
		vector<coord> new_starts;
		
		int cluster_size = 1;
		search_loop(new_starts,positions[0],matrix,length,width);
		
		//set searched position to 4 to prevent research and mix up with other fires
		matrix[positions[0].get_y()][positions[0].get_x()] = 4;
		//erase from positions matrix to prevent re-search
		positions.erase(positions.begin());
		
		//continue until edge of cluster has been found
		while(new_starts.size() !=0)
		{
			search_loop(new_starts,new_starts[0],matrix,length,width);
			matrix[new_starts[0].get_y()][new_starts[0].get_x()] = 4;
			cluster_size++;
			//erase from positions matrix
			for (int i =0; i<positions.size();i++)
			{
				if(positions[i] == new_starts[0]) positions.erase(positions.begin()+i);
			}
			new_starts.erase(new_starts.begin());		
		}
		clusters << cluster_size << endl;
	}				
		
}				
#endif	
