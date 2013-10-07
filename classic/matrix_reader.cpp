#ifndef MATRIX_READER_CPP
#define MATRIX_READER_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void matrix_reader(ifstream& input_file, char& c, string& str, vector<int *>& forest, int *forest_temp)
{
	while (c != EOF) // check if end of file has been reached
	{
		//read in one line of the matrix
		getline(input_file,str,'\n');
		//clear space for the line of the matrix for forest and gump
		forest_temp = new int[str.length()];
	
		for (int i =0; i < str.length(); i++) //puts string into 1D array
		{
			forest_temp[i] = int(str.at(i))-48; //Textfile -everything stored in ascii!
		}
	
		forest.push_back(forest_temp); //put pointer to forest_temp into vector of 1D array addresses
		c = input_file.peek();
	}
}

#endif
	
