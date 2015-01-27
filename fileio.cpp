// basic file io.
// script reads a file line by line, tokenizes by tab, prints first two 
// columns to an output file.
// input args: 1) input file 2) output file.

// To compile:
// g++ -I/opt/local/include -L/opt/local/lib fileio.cpp

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
using namespace std;
using namespace boost;

int main (int argc, char* argv[]) {
   // I/O
    ifstream in; ofstream out; 
    in.open(argv[1]);
    out.open(argv[2]);

	const int MAX_LINELEN=1000;
    char line1[MAX_LINELEN];
    
   while (in.good())
    {
        in.getline(line1, MAX_LINELEN);
        if (std::strcmp(line1,"") > 0){ // if not empty
            vector<string> t1; // tokenize read line. 
            boost::split(t1, line1, boost::is_any_of("\t"));
           	int next = boost::lexical_cast<int>(t1[1]); next++;		
			out << t1[0] << "\t" << t1[1] << endl;
        }
    }
    in.close();out.close();
    return 0;
}
         
