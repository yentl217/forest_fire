#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
using namespace std;

//TODO separate matrix reader part from simulation part
//Initialising
int num_steps = 2;
double prob_f = 1; //probability of tree NOT burning independent of neighbours
double prob_g = 0; // probability of tree growing
double prob_b = 0; //probability of a tree NOT setting a neighbour on fire if it is burning

void one_step(vector<int *>& forest_record, vector<int *>& forest_modified, int width, int length)
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
			//a tree's probability of becoming on fire is 1-(prob_f)+1-(prob_b)^no_of_fiery_neighbours
			if (forest_record[y][x] == 2)
			{
				//count the number of neighbouring fires 
				int neighbour_fires=0;
				if (x == (length-1)) 
				{
					if (forest_record[y][0] == 1) neighbour_fires++; //periodic boundaries along
				} 
				else if (forest_record[y][x+1] == 1) neighbour_fires++;
				if (x == 0)
				{
					if (forest_record[y][length-1] ==1) neighbour_fires++; //periodic boundaries along x
				}
				else if (forest_record[y][x-1] == 1) neighbour_fires++;
				
				if (y == (width-1))
				{ 
					if (forest_record[0][x] == 1) neighbour_fires++;//periodic boundaries along y
				}
				else if (forest_record[y+1][x] == 1) neighbour_fires++;
				
				if (y == 0)
				{
					if (forest_record[width-1][x] == 1) neighbour_fires++;//periodic boundaries along y
				}
				else if (forest_record[y-1][x] == 1) neighbour_fires++;
				
				if ( 1.0*rand()/RAND_MAX <= (2-prob_f-pow(prob_b,neighbour_fires))) forest_modified[y][x] = 1;
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
	
	//create two forests -array of booleans
	//TODO change vector to array at end
	ifstream input_file("input"); //TODO check file has opened without error
	string str;
	char c = 'h';
	//create two copies of the forest, named forest and gump
	int *forest_temp;
	int *gump_temp;
	vector<int *> forest;
	vector<int *> gump;
	
	//Making forest and gump
	while (c != EOF) // check if end of file has been reached
	{
		//read in one line of the matrix
		getline(input_file,str,'\n');
		//clear space for the line of the matrix for forest and gump
		forest_temp = new int[str.length()];
		gump_temp = new int[str.length()];
		
		for (int i =0; i < str.length(); i++) //puts string into 1D array
		{
			forest_temp[i] = int(str.at(i))-48; //Textfile -everything stored in ascii!
			gump_temp[i] = forest_temp[i]; //copy data from forest into gump in same structure 
		}
		
		forest.push_back(forest_temp); //put pointer to forest_temp into vector of 1D array addresses
		gump.push_back(gump_temp); //puts pointer to gump_temp into vector of 1D array addresses
		c = input_file.peek();
	}
	
	//main simulation loop
	//TODO: make bitmap images...
	int length = str.length();
	int width = forest.size();
	for (int i = 0; i <num_steps; i+=2) //two steps per loop!
	{
		//first use gump as record, modify forest
		one_step(gump,forest,length,width);
		//then use forest as record, modify gump
		one_step(forest,gump,length,width);
	}
	for (int y=0; y < width; y++)
	{
		for (int x=0; x<length; x++)
		{
			cout << gump[y][x] << endl;
		}
	}
	return 0;
} 		 
