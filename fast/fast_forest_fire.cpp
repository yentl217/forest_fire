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
	double p_over_f = 1000;
	const int length = atoi(argv[1]);
	const int width = atoi(argv[2]);
	int num_steps = atoi(argv[3]);
	
	ofstream outputfile(argv[4]);
	
	int** forest;
	forest = new int *[width];
	for(int i =0; i<length; i++){ forest[i] = new int[length]; }
	
	srand (time(NULL));
	
	for(int j=0;j<width;j++)
	{
		for(int i=0;i<length;i++)
		{
			forest[j][i] = 0;
		}
	}
	
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
		
		//Find arbitrary site
		int rand_x = rand() % length;
		int rand_y = rand() % width;
		
		//If an empty site is found, find p/f sites and grow trees if it is empty
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
		
		//Otherwise, if a tree is found, set it on fire and ignite the whole cluster; Cluster size is counted.
		else if (forest[rand_y][rand_x] == 2)
		{
			fast_count(forest,length,width,coord(rand_x,rand_y),cluster);
			num_trees -= cluster.size();
			//outputfile << cluster.size() << endl;
		}
		outputfile << double(num_trees)/(length*width) << endl;
	}
	
	//deallocate memory for forest
	for(int i=0; i<width;i++)
	{
		delete forest[i];
	}
	delete forest;
	return 0;
}
		
