/* 
 Example of using key-value pairs (std::maps) in C++.
 */
#include <string>
#include <map>
#include <iostream>
using namespace std;


void initMap(std::map<string, int> &temp_map) {
    temp_map["CG"]=0;
    temp_map["CA"]=0;
};

//#define TEST_MODE 1

/* ***************************************************************************
 Main function
 ***************************************************************************  */

int main (int argc, char* argv[]) {
    std::map<string, int> totM; // declare
    initMap(totM);  // initialize
    
    string ctxt="CG";
    totM[ctxt]++; // add to total

    typedef map<string, int>::const_iterator MapIterator;
for (MapIterator iter = totM.begin(); iter != totM.end(); iter++)
{
    cout << iter->first << " -> " << iter->second << endl;
}
   
    // print map.
}
    

