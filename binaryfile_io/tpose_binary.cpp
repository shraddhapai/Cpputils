/* * Seek and print specific records from a table with fixed-width columns.
   * Each field is assumed to be 1 byte long and containing genotype encoded
   * as {0,1,2}.
   *
   * Say the dataset has M snps in N patients. 
   * 
   * Then, input file is MxN file where each row has N chars of {0,1,2}. 
   * There is no whitespace between characters.
   * 
   * Output file is a table of tab-delimited genotypes.
   * The file has P<=M rows, where P is the number of records requested.
   * Each row has (Nx2) tab-separated entries; each genotype is now encoded
   * in binary format across two columns. 
   * 
   * example: if a row of input file has: 021, then the corresponding
   * output would be 0t0t1t0t0t1 where t is the tab separator.
   * 
   * to see i/o params and example usage, type './getSNPrecords' at command line
   * 
   * example input file: see files/bintest.txt
   */

#include <stdio.h>	// fopen, fread, fclose
#include <iostream> // cout and endl
#include <fstream> // writing output file
#include <string>
#include <stdlib.h> // atoi
#include <vector>
#include <sstream>	// tokeniz   e comma-separated integers
using namespace std;


int main(int argc, char* argv[])
{

	if (argc < 4) {
		cerr << endl << endl;
		cerr << "-----------------------------------------------------------";
		cerr << endl;
		cerr << "Usage: " << endl << endl;
		cerr << argv[0] << " infile n idx outfile";
		cerr << endl << endl;
		cerr << "infile: (character) path to input file" << endl;
		cerr << "n: (integer) num patients in each row"<<endl;
		cerr << "idx: comma-separated integers of rows ";
		cerr << "to retrieve" << endl;
		cerr << "outfile: (character) path to output file" << endl;
		cerr << endl;
		cerr << "Example:" << endl;
		cerr << "\t" << argv[0] << " files/tpose_binary.txt 5 2,5,8 out.txt" << endl;
		cerr << "Here we retrieve rows 2,5, and 8.";
		cerr << " Each row has 5 genotypes." << endl;
		cerr << endl << endl;
		cerr << "-----------------------------------------------------------";
		cerr << endl;
		return -1;
	}
	// parse I/O args
	char* inFile(argv[1]);
	int REC_SIZE=atoi(argv[2]);
	istringstream ss(argv[3]); 
	char* outFile(argv[4]);

	string token;
	std::vector<int> v;
	while(std::getline(ss,token,',')) {
		v.push_back(atoi(token.c_str()));
	}

	cout << "Record size is: " << REC_SIZE << endl;
	FILE *pFile;
	pFile = fopen(inFile,"rb");
	if (pFile==NULL){
		cerr << " unable to open file for reading." <<endl;
		return -1;
	}
	cout << "   opened file" << endl;
	int BSIZE=1;
	char buffer[BSIZE]; // XXS where X is {0,1} and S is whitespace

	/*int ctr=0;
	while ((fread(buffer,BSIZE,1,pFile)==1) && (ctr<=10)) {
		cout << ctr << "*" << buffer[0]<<"*" <<endl;
		ctr++;
					}
	*/

	// array to hold transpose data (rows=patients, columns SNPs)
	char** ary = new char*[REC_SIZE];  
	for (unsigned int i=0; i< REC_SIZE; i++){
		ary[i] = new char[v.size()*2]; //v.size() SNPS * 2 chars per SNP
	}

	// fetch each SNP in this pathway
	for (int i=0; i<v.size(); i++) {
		long nextseek = (v[i]-1)*(REC_SIZE+1);
		//cout << "#" << v[i] << ": pos "<< nextseek << endl;
		fseek(pFile,nextseek, 0);
		int ctr=BSIZE; int pt_num=0;
		//cout <<"*";
		while ((fread(buffer, BSIZE, 1, pFile) == 1)&&(ctr<=REC_SIZE)) {
			//cout << "(" << ctr << ")" << "=>";
			//cout << "*"<< buffer[0] << "*";
			char outchar[3]; outchar[2]=' ';
			if (buffer[0]=='0') {
				outchar[0]='0';outchar[1]='0';
			} else if (buffer[0]=='1') {
				outchar[0]='0'; outchar[1]='1';
			} else if (buffer[0]=='2') {
				outchar[0]='1'; outchar[1]='0';
			} 
			// SNP i goes into columns 2i-,2i-1
			ary[pt_num][2*i]=outchar[0];
			ary[pt_num][(2*i)+1]=outchar[1];
			//cout << outchar;

			ctr+=BSIZE;
			pt_num++;
		}
	}
	
	fclose(pFile);

	// now write transposed matrix to output file
	// this is patient-by-SNP-genotype
	ofstream out;
	out.open(outFile);

	char NEWLINE[]={'\n'};
	cout << "* Writing transposed matrix to file:" << endl;
	cout << outFile << endl;
	for (int i=0; i<REC_SIZE; i++) {
		int ctr=0;
		for (int j=0; j<(v.size()*2); j+=2) {
			out << ary[i][j] << "\t" << ary[i][j+1];
			if (ctr<(v.size()-1)) out << "\t";
			ctr++;
		}
		out << "\n";
	}
	out.close();
	cout << "file closed." << endl;
	// clean up, because we used 'new' to allocate array
	for (int i=0; i < REC_SIZE; i++) {
		delete [] ary[i];
	}
	delete [] ary;

return 0;
}



