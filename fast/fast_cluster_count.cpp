#ifndef FAST_CLUSTER_COUNT_CPP
#define FAST_CLUSTER_COUNT_CPP

#include <iostream>
#include "tools.cpp"
#include "coord.h"
#include "vector"
using namespace std;

//This function checks whether each of the four cells adjacent to start contains a tree, and if so, adds that cell to new_starts provided it is not already there.
void search_loop(vector<coord>& new_starts, coord start,int **trees, int length, int width)
{
	coord current_searches[4];
	new_searches(current_searches,start,length,width); //initialise current_searches on the four cells adjacent to start
	
	for(int i = 0; i<4; i++) 
	{
		int count=0;
		if (trees[current_searches[i].get_y()][current_searches[i].get_x()] == 2) //check whether each cell adjacent to start contains a tree
		{
			while (count <new_starts.size()) //check whether that cell is already in new_starts
			{
				if(new_starts[count] == current_searches[i]) break;
				count++;
			}
			if (count == new_starts.size()) new_starts.push_back(current_searches[i]); //if the cell is not already in new starts, add it to new_starts
		}
	}
}

//This function builds up the cluster containing the cell init, and sets every cell in that cluster on fire.
void fast_count(int **forest, int length, int width, coord init, vector<coord> &cluster)
{
	vector<coord> new_starts; //evolving vector of cells that are in the same cluster as init and are not yet on fire.
	
	cluster.push_back(init);//initialise cluster around init (empty from main program)
	forest[init.get_y()][init.get_x()] = 1; //sets init on fire (cell with status 1)
	
	search_loop(new_starts,init,forest,length,width); //initialise new_starts with cells adjacent to init that also contains a tree (cell with status 2)
	while(new_starts.size() !=0 ) //loop stops when we can no longer find trees in the same cluster as init that's not already on fire.
	{
		search_loop(new_starts,new_starts[0],forest,length,width); //add to new_starts any cell adjacent to the first element of new_starts that contains a tree, if that cell is not already present in new_starts
		cluster.push_back(new_starts[0]); //add the first element of new_starts to the cluster around init
		forest[new_starts[0].get_y()][new_starts[0].get_x()] = 1; // sets the first element of new_starts on fire
		new_starts.erase(new_starts.begin()); //delete the first element of new_starts
	}
}

#endif
