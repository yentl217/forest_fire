#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include "matrix_reader.cpp"
#include "cluster_count.cpp"
#include "coord.h"

using namespace std;

//Initialising
int num_steps = 2;
double prob_f = 1; //probability of tree NOT burning independent of neighbours
double prob_g = 0; // probability of tree growing
double prob_b = 0; //probability of a tree NOT setting a neighbour on fire if it is burning

void one_step(vector<int *>& forest_record, vector<int *>& forest_modified, int length,int width)
{
	for (int y = 0; y<width; y++)
	{
		for (int x = 0; x<length; x++)
		{	
			//a tree has prob_g of growing in an empty space
			if (forest_record[y][x] == 0)
			{
				if (1.0*rand()/RAND_MAX <= prob_g) forest_modified[y][x] = 2;
				else forest_modified[y][x] = 0;
			}	
			//a tree's probability of becoming on fire is 1-(prob_b)^no_of_fiery_neighbours*prob_f
			if (forest_record[y][x] == 2)
			{
				//count the number of neighbouring fires 
				int neighbour_fires=0;
				coord new_checks[4];
				new_searches(new_checks,coord(x,y),length,width);
				for(int i = 0; i<4; i++)
				{
					if (forest_record[new_checks[i].get_y()][new_checks[i].get_x()] == 1) neighbour_fires++;
				}
				
				if ( 1.0*rand()/RAND_MAX <= (1-pow(prob_b,neighbour_fires)*prob_f)) forest_modified[y][x] = 1;
				else forest_modified[y][x] = 2;
			}		
			//a burning tree becomes an empty cell
			if (forest_record[y][x] == 1) forest_modified[y][x] = 0;
		}
	}
}	

int main()
{
	srand (time(NULL)); //Initialise random seed
	
	//Set up reading in matrix from input file
	ifstream input_file("input"); //TODO check file has opened without error
	string str;
	char c = 'h';
	int *forest_temp;
	int *gump_temp;

	//create two copies of the forest, named forest and gump
	//They are vectors of pointers to integer arrays containing the entries for each row
	vector<int *> forest;
	vector<int *> gump;
	
	//read in matrix from input_file
	matrix_reader(input_file,c,str,forest,gump,forest_temp,gump_temp);
	
	//main simulation loop
	int length = str.length();
	int width = forest.size();
	
	for (int i = 0; i <num_steps; i+=2) //two steps per loop!
	{
		//first use gump as record, modify forest
		one_step(gump,forest,length,width);
		cluster_count(gump,length,width);
		//then use forest as record, modify gump
		one_step(forest,gump,length,width);
		cluster_count(forest,length,width);
	}
	return 0;
} 		 
