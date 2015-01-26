#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// tests membership of string "chrom" in vector "v". Returns 1 if "chrom" exactly matches an element of "v". Else returns 0.
bool is_chrom( std::vector<std::string> v, string chrom ) {
int val=0;
for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it) {
		if (chrom.compare(*it) == 0) {
				val=1;
		}
}
return val;
}

/*
   Demo of string operations.
   */

int main (int argc, char* argv[]) {
// initialize vector of strings
const char *chroms[] = { "chr1","chr2","chr3","chr4","chr5","chr6","chr7","chr8", "chr9","chr10","chr11","chr12","chr13","chr14","chr15","chr16","chr17","chr18","chr19","chr20","chr21","chr22","chrX","chrY","chrM" };
std::vector<std::string> chromVec(chroms, chroms + 25);

// print vector contents
for (std::vector<std::string>::iterator it = chromVec.begin(); it!=chromVec.end(); ++it) {
	std::cout << " " << *it << std::endl;
}

// test membership in vector
string chrom="chr5";
cout << chrom << " in vec? :  " << is_chrom(chromVec, chrom) << endl;
chrom="chr5_unmapped";
cout << chrom << " in vec? :  " << is_chrom(chromVec, chrom) << endl;

string joiner;
string s1="chr1"; string s2=".txt";
joiner = s1 + s2;
cout << joiner << endl;
}

