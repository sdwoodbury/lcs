/*
	Stuart Woodbury
	CMSC 441
	Project 1
	Multithreaded LCS
	
	-This program requires an input file in the same directory as the driver. 
	-the input file must have two lines. 
	-The input must consist of A, C, T, or G, separated by spaces
	-the two sequences must be of the same length

	-The lcs is calculated
*/
#include <vector>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main(int argc, char **argv){

	if(argc != 2){
		std::cout << "invalid number of command line parameters\n";
		return 1;
	}

	/*std::cout << argv[1] << std::endl;*/
	std::ifstream file;
	file.open(argv[1]);

	std::string line; /*for reading from file*/
	std::vector<char> sequences[2];

	int count = -1; /*used for verifying that the file is formatted properly*/
	int line_length = 0; /*used for line length*/
	char chars[] = {'G', 'C', 'T', 'A'};
	std::set<char> input (chars, chars+5);
	std::set<char>::iterator it;

	while( getline(file, line)){
		count++;
		if(count > 1)
			break;

		line_length = line.size();
		for(int i = 0; i < line_length; i++){
			it=input.find(line[i]);
			if(it != input.end()){
				sequences[count].push_back(line[i]);
			}
		}
	}

	file.close();

	if(count != 1){
		std::cout << "invalid number of lines in the file\n";
		return 1;
	}

	std::vector<int> val_initializer(sequences[0].size() + 1, 0);
	std::vector< std::vector<int> > val_table(sequences[0].size() + 1, val_initializer);

	std::vector<char> char_initializer(sequences[0].size() + 1, '-');
	std::vector<std::vector<char> > char_table(sequences[0].size() + 1, char_initializer);

	int sequence_length = sequences[0].size() + 1;
	for(int i = 1; i < sequence_length; i++){
		#pragma omp parallel for
		for(int k = i; k > 0; k--){
			int j = i - k + 1;
			if(sequences[0][k-1] == sequences[1][j-1]){
				val_table[k][j] = val_table[k-1][j-1] + 1;
				char_table[k][j] = '+';
			} else if(val_table[k-1][j] >= val_table[k][j-1]){
				val_table[k][j] = val_table[k-1][j];
				char_table[k][j] = '^';
			} else {
				val_table[k][j] = val_table[k][j-1];
				char_table[k][j] = '<';	
			}
		}
	}

	for(int j = 2; j < sequence_length; j++){
		#pragma omp parallel for
		for(int i = sequence_length - 1; i > (j-1); i--){
			int k = j + sequence_length - i - 1;
			if(sequences[0][i-1] == sequences[1][k-1]){
				val_table[i][k] = val_table[i-1][k-1] + 1;
				char_table[i][k] = '+';
			} else if(val_table[i-1][k] >= val_table[i][k-1]){
				val_table[i][k] = val_table[i-1][k];
				char_table[i][k] = '^';
			} else {
				val_table[i][k] = val_table[i][k-1];
				char_table[i][k] = '<';
			}
		}
	}


	/*for(unsigned int i = 0; i < val_table.size(); i++){
		for(unsigned int j = 0; j < val_table[0].size(); j++){
			std::cout << val_table[i][j] << ' ';
		}
		std::cout << '\n';
	}

	for(unsigned int i = 0; i < val_table.size(); i++){
		for(unsigned int j = 0; j < val_table[0].size(); j++){
			std::cout << char_table[i][j] << ' ';
		}
		std::cout << '\n';
	}*/

	int j = val_table.size() - 1;
	int i = val_table.size() - 1;

	std::vector<int> lcs;

	while(j > 1 and i > 1){
		if(char_table[i][j] == '+'){
			lcs.insert(lcs.begin(),sequences[0][i-1]);
			i -= 1;
			j -= 1;
		}
		if(char_table[i][j] == '^'){
			i -= 1;
		}
		if(char_table[i][j] == '<'){
			j -= 1;
		}
	}

	for(unsigned int i = 0; i < lcs.size(); i++){
		std::cout << char(lcs[i]);
	}
	//std::cout << '\n';

	//std::cout <<"the lcs is length " << val_table[sequences[0].size()][sequences[0].size()] << '\n';
	return 0;
}
