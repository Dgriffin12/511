#include <iostream>
#include "Replace.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "invalid number of arguments! #: " << argc << endl;
	}
	string old_string = argv[1];
	string new_string = argv[2];

	Replace *replacer = new Replace(argv[3]);
	replacer->replace(old_string, new_string);
	delete replacer;
	return 0;
}	
