/* transposes matrix in input file, writes transpose to output file
   */

#include <stdio.h>	// fopen, fread, fclose
#include <iostream> // cout and endl
#include <string>
#include <stdlib.h> // atoi
#include <vector>
#include <sstream>	// tokenize comma-separated integers
using namespace std;

int main(int argc, char* argv[])
{
}
	// parse I/O args
	char* inFile(argv[1]);
	int n=10;			// num columns
	int m=10;			// num records
	int BSIZE=3;		// column width in bytes
	int REC_SIZE=NUM_RECS*BSIZE;

	// array to hold transpose data
	char** ary = new char*[m*2]; // each genotype takes up two chars
	for (int i=0; i< m; i++){
		ary[i] = new char[n];
	}

	char* outFile="out.txt";

	cout << "Record size is: " << REC_SIZE << endl;
		FILE *pFile;
		pFile = fopen(inFile,"rb");

	if (pFile!=NULL){
		cout << "opened file" << endl;
		char buffer[BSIZE]; // XXS where X is {0,1} and S is whitespace
		// read a record, 3 bytes at a time
		int ctr=BSIZE;
		while ((fread(buffer, BSIZE, 1, pFile) == 1)&&(ctr<=REC_SIZE)) {
			//cout << "(" << ctr << ")" << "=>";
			cout << buffer[0] << buffer[1];
			ctr+=BSIZE;
			if (ctr <=REC_SIZE) {
				cout << "\t";
			} else {
				cout << endl;
			}
		}
	}
	fclose(pFile);

	// write to file

	// clean up, because we used 'new' to allocate array
	for (int i=0; i < m; i++) {
		delete [] ary[i];
	}
	delete [] ary;
	return 0;
}



