/* * Seek and print specific records from a table with fixed-width columns.
   * Each field is assumed to be 3 bytes long, and only the first two bytes
   * are written to output file.
   * 
   * to build: type 'make' at commandline
   * 
   * to see i/o params and example usage, type './getSNPrecords' at command line
   * 
   * example input file: see files/bintest.txt
   */

#include <stdio.h>	// fopen, fread, fclose
#include <iostream> // cout and endl
#include <string>
#include <stdlib.h> // atoi
#include <vector>
#include <sstream>	// tokenize comma-separated integers
using namespace std;

/* Input args:
   1) REC_SIZE : (integer) record size in bytes
   */

int main(int argc, char* argv[])
{

	if (argc < 3) {
		cerr << endl << endl;
		cerr << "-----------------------------------------------------------";
		cerr << endl;
		cerr << "Usage: " << endl << endl;
		cerr << argv[0] << " infile record_size rec_to_fetch outfile";
		cerr << endl << endl;
		cerr << "infile: (character) path to input file" << endl;
		cerr << "record_size: (integer) size in bytes of each table row"<<endl;
		cerr << "idx_to_fetch: comma-separated integers of rows ";
		cerr << "to retrieve" << endl;
		cerr << "outfile: (character) path to output file" << endl;
		cerr << endl;
		cerr << "Example:" << endl;
		cerr << "\t" << argv[0] << " files/bintest.txt 30 2,5,8" << endl;
		cerr << "Here we retrieve rows 2,5, and 8 from files/bintest.txt";
		cerr << " Each row is of 30 bytes.";
		cerr << endl << endl;
		cerr << "-----------------------------------------------------------";
		cerr << endl;
		return -1;
	}
	// parse I/O args
	char* inFile(argv[1]);
	int REC_SIZE=atoi(argv[2]);
	istringstream ss(argv[3]); 

	string token;
	std::vector<int> v;
	while(std::getline(ss,token,',')) {
		v.push_back(atoi(token.c_str()));
	}

	
	// get 2nd and 5th record - assume we get these sorted
	//std::vector<int> v;
	//v.push_back(2);
	//v.push_back(5);

	cout << "Record size is: " << REC_SIZE << endl;
		FILE *pFile;
		pFile = fopen(inFile,"rb");
		if (pFile!=NULL){
			cout << "opened file" << endl;
			int BSIZE=3;
			char buffer[BSIZE]; // XXS where X is {0,1} and S is whitespace
			
			for (int i=0; i<v.size(); i++) {
				long nextseek = (v[i]-1)*REC_SIZE;
				//cout << "#" << v[i] << ": pos "<< nextseek << endl;
				fseek(pFile,nextseek, 0);
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
		}
	fclose(pFile);
	return 0;
}



