#include <time.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

	int len = atoi(argv[1]);
	int next;
	char values[] = {'A', 'C', 'G', 'T'};

	std::ofstream file;
	file.open("sequences", std::ios::out|std::ios::trunc);
	
	srand(time(NULL));
	for(int i = 0; i< len; i++){
		next = rand() % 4;
		file << values[next];
	}
	file << '\n';
	for(int i = 0; i< len; i++){
		next = rand() % 4;
		file << values[next];
	}

	file.close();
	return 0;
}
