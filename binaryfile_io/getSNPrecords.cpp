/* Convert a text file to a fixed-width binary for fast seek
   * Context: indexing for SNPs in a pathway from a large patient-by-SNP table
Input file format: Tab-delimited records separated by newlines.
Our goal is to seek by rows.
Each cell of the table contains {0,1,2}

Output file format: Fixed-width binary file where SNPS are encoded as 
bytes.

   */

#include <stdio.h>
using namespace std;

int main(int argc, char* argv[])
{
			FILE *pFile;
			pFile = fopen("bintest.txt","r");
			if (pFile!=NULL){
				char buffer[sizeof(int)];
				std::cout << "buffer size is: " << buffer << std::endl;
				while (fread(buffer, sizeof buffer, 1, pFile) == 1) {
					std::cout << "read *" << buffer << "*" << endl;
				}
				if (feof(pFile)) {
					std::cout << "reached end of file" << endl;
				} else {
					std::cout << "some other error" << endl;
				}
			}

}



