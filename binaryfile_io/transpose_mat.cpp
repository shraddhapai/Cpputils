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
	// usage info
	if (argc < 4) {
		cerr << endl << endl;
		cerr << "---------------------------------------------------------";
		cerr << endl;
		cerr << "Usage: " << endl << endl;
		cerr << argv[0] << " infile m n outfile";
		cerr << endl << endl;
		cerr << "infile: (character) path to input file" << endl;
		cerr << "m: (integer) num rows in table" << endl;
		cerr << "n: (integer) num cols in table ; " << endl;
		cerr << " assumes each record 3 bytes wide, with last byte being";
		cerr << " whitespace" << endl;
		cerr << "outfile: (character) path to output file" << endl;
		cerr << endl;
		cerr << "Example:" << endl;
		cerr << "\t" << argv[0] << " files/bintest.txt 10 8 ";
		cerr << " out.txt"; 
		cerr << "Here a 10x8 table would be read from files/bintest.txt, ";
		cerr << "transposed and written to out.txt";
		cerr << endl << endl;
		cerr << "---------------------------------------------------------";
		cerr << endl;
		return -1;
	}

	// parse I/O args
	string inFile("files/bintest.txt"); //argv[1]);
	string outFile("out.txt");
	// file params
	int n=10;			// num columns
	int m=8;			// num records
	int BSIZE=3;		// column width in bytes
	int REC_SIZE=n*BSIZE;

	cout << "Table with "<<m << "records, " << n << " columns" << endl;

	// array to hold transpose data
	char** ary = new char*[n]; 
	for (unsigned int i=0; i< n; i++){
		ary[i] = new char[m*2]; // m patients => m*2 genotypes
	}

	FILE *pFile;
	pFile = fopen("files/bintest.txt","rb");
	if (pFile==NULL){ 
		cerr << "could not open file" << endl;
		return -1;
	}
	cout << "opened file" << endl;
	char buffer[BSIZE]; 
	int i=0;
	int j=0; 
	int numel=0;
	while ((fread(buffer, BSIZE, 1, pFile) == 1) && (numel<=(m*n)) ) {
		ary[j][i]=buffer[0]; 
		ary[j][i+1]=buffer[1];
		// print i,j and contents
		// cout << "[" << j << ","<< i << "]=";
		// cout <<  ary[j][i] << ary[j][i+1] << " ";
		j++; numel++;
		if (j == n) {
			i+=2; // move to next column
			j=0;
			// cout << endl;
		}
	}
	fclose(pFile);
	cout << "closed file" << endl;

	// write to file
	//FILE *wFile;
	//wFile = fopen(outFile,"wb");
	cout << "transposed matrix" << endl;
	for (int i=0; i<n; i++) {
		for (int j=0; j<(2*m); j+=2) {
			// print matrix
			//cout << ary[i][j] << ary[i][j+1] << " ";
		}
		cout << endl;	
	}
	//close(wFile);
	
	// clean up, because we used 'new' to allocate array
	for (int i=0; i < m; i++) {
		delete [] ary[i];
	}
	delete [] ary;
}

