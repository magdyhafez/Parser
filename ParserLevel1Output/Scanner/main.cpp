#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "scanner.h"
#include "treeNode.h"
using namespace std;

int main()
{
    string line ;
    queue<string> Queue;
    ifstream myfile ("examples.txt");
    // reading from file
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            Queue.push(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

	scannerOutput(Queue);

	while (!TokenTypesFinished() && !TokenValuesFinished())
	{
		cout << getTokenValue() << "   " << getTokenType() << endl;
	}
	
	getchar();
	return 0;
}
