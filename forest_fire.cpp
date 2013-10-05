#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include "matrix_reader.cpp"
#include "coord.h"
#include "cluster_count.cpp"

using namespace std;

//Initialising
//TODO: Make all these command line options
int num_steps = 4;
double prob_g = 0.0;//1.0/16000; // probability of tree growing
//TODO: so close to 1 possibly the probability may be distorted
double prob_f = 1.0;//1.0-prob_g/16000.0; //probability of tree NOT being struck by lightening
double prob_b = 0.0; //probability of a tree NOT setting a neighbour on fire if it is burning	

ofstream clusters("cluster_register");

int main()
{
	srand (time(NULL)); //Initialise random seed
	
	//Set up reading in matrix from input file TODO:Make this an argument option
	ifstream input_file("input"); //TODO check file has opened without error
	string str;
	char c = 'h';
	int *forest_temp;

	//create two copies of the forest, named forest and gump
	//They are vectors of pointers to integer arrays containing the entries for each row
	vector<int *> forest;
	
	//read in matrix from input_file
	matrix_reader(input_file,c,str,forest,forest_temp);
	
	int length = str.length();
	int width = forest.size();
	
	//generate start forests (TODO: make this an argument option)
	
	/*int length=16438;
	int width=16438;
	vector<int *> forest;
	int *forest_temp;
	
	cout.precision(15);
	cout << prob_g << endl;
	cout << prob_f << endl;
	cout << prob_b << endl;
	
	for(int j=0; j<width; j++)
	{
		forest_temp = new int[length];
		for (int i=0; i<length; i++)
		{
			forest_temp[i] = 0;
		}
		forest.push_back(forest_temp);
	}*/
	
	vector<coord> list_fires;
	vector<coord> list_trees;
	
	//main simulation loop
	for (int i = 0; i <num_steps; i++)
	{
		
		for (int y = 0; y<width; y++)
		{
			for (int x = 0; x<length; x++)
			{	
				//a tree has prob_g of growing in an empty space
				if (forest[y][x] == 0)
				{
					if (1.0*rand()/RAND_MAX <= prob_g) forest[y][x] = 2; 
				}
				else if (forest[y][x] == 4)
				{
					if (1.0*rand()/RAND_MAX <= prob_g) forest[y][x] = 2;
					else forest[y][x] = 0;
				}	
				//a tree's probability of becoming on fire is 1-(prob_b)^no_of_fiery_neighbours*prob_f
				else if (forest[y][x] == 2)
				{
					//count the number of neighbouring fires 
					int neighbour_fires=0;
					coord new_checks[4];
					new_searches(new_checks,coord(x,y),length,width);
					for(int i = 0; i<4; i++)
					{
						if (forest[new_checks[i].get_y()][new_checks[i].get_x()] == 1) neighbour_fires++;
					}
				//If a tree will burn, add it to the trees list
					if ( 1.0*rand()/RAND_MAX <= (1-pow(prob_b,neighbour_fires)*prob_f)) list_trees.push_back(coord(x,y));
				}		
				//Add burning tree to list
				else if (forest[y][x] == 1) list_fires.push_back(coord(x,y));
			}
		}
		cluster_count(forest,length,width,list_fires,clusters);
		for (int y=0; y<width; y++)
		{
			for (int x=0; x<length; x++)
			{
				for (int i =0; i<list_trees.size(); i++)
				{
					//update all trees that should burn to burning trees
					if (coord(x,y) == list_trees[i]) 
					{
						forest[y][x] = 1;
						list_trees.erase(list_trees.begin()+i);
					}
				}
			}
		}
		cout << i << endl;
	}
	
	//save state of simulation
	ofstream sim("simulation_state");
	for(int j=0; j<width; j++)
	{
		for(int i=0; i<length;i++)
		{
			sim << forest[j][i];
		}
		sim << endl;
	}
	
	//deallocate memory taken up by forest
	for(int i =0; i<width;i++)
	{
		delete forest[i];
	}
	return 0;
} 		 
