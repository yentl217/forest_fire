#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <fstream>
#include "tools.cpp"
#include "fast_cluster_count.cpp"
#include "coord.h"
using namespace std;

//TODO: make these command line arguments!

//keep track of number of trees planted
int num_trees = 0;

int main(int argc, char * const argv[])
{
	int p_over_f = 1000; //p/f ratio
	
	//command-line arguments
	const int length = atoi(argv[1]); // length of forest fire grid
	const int width = atoi(argv[2]); // width of forest fire grid
	int num_steps = atoi(argv[3]); // how many steps the simulation should run for
	
    ofstream tree_density_output("tree_density.txt"); //output file for tree density at each simulation step
    ofstream final_forest_output("final_forest.txt"); //output file showing status of cells in final forest
    ofstream clusters_output("clusters.txt"); //output file showing status of cells in final forest

	
    //initialise forest fire model as 2D grid of integers, each describing the status of the cell (0: empty, 1: burning, 2: tree)
	int** forest;
	forest = new int *[width];
	for(int i =0; i<length; i++){ forest[i] = new int[length]; }
	
	// initialise random number generator by time at which program started running
	srand (time(NULL));
	
    //forest starts off completely empty
	for(int j=0;j<width;j++)
	{
		for(int i=0;i<length;i++)
		{
			forest[j][i] = 0;
		}
	}
	
	//initialise vector to hold any cluster found
	vector<coord> cluster;
	
	//Main simulation loop
	for(int step =0; step<num_steps; step++)
	{
		cout << "On step " << step+1 << endl;
		
		//Burn down all the burning trees
		while(cluster.size() != 0)
		{
			forest[cluster[0].get_y()][cluster[0].get_x()] = 0;
			cluster.erase(cluster.begin());
		}
		
		//Find random site
		int rand_x = rand() % length;
		int rand_y = rand() % width;
		
		//If random site is empty, find p/f sites and grow trees if it is empty
		if (forest[rand_y][rand_x] == 0)
		{
			for (int i =0; i <p_over_f; i++)
			{
				int rand_grow_x = rand() % length;
				int rand_grow_y = rand() % width;
				if (forest[rand_grow_y][rand_grow_x] == 0) 
				{
					forest[rand_grow_y][rand_grow_x] = 2;
					num_trees++;
				}
			}
			
		}
		
		//Otherwise, if a tree is found, ignite the whole cluster it is in and count it
		else if (forest[rand_y][rand_x] == 2)
		{
			fast_count(forest,length,width,coord(rand_x,rand_y),cluster);
			num_trees -= cluster.size();
            //clusters_output << cluster.size() << endl;
		}
		tree_density_output << double(num_trees)/(length*width) << endl;
	}
	
	//output entire forest at last step
	for(int j=0;j<width;j++)
	{
		for(int i=0;i<length;i++)
		{
			final_forest_output << forest[j][i] << ",";
		}
		final_forest_output << endl;
	}

	
	//deallocate memory for forest
	for(int i=0; i<width;i++)
	{
		delete forest[i];
	}
	delete forest;
	return 0;
}
		
