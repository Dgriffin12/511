#include <iostream>
#include "StreamSource.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "invalid number of arguments! #: " << argc << endl;
	}
	string old_string = argv[1];
	string new_string = argv[2];

	StreamSource ss(argv[3], old_string, new_string);
	char ch;
	int match_count = 0;
	int test = 0;
	//MAIN LOOP
	while(ss.get(ch) != EOF)
	{
		if(ch == EOF)
			break;
		test++;
		if( !ss.replacing() && ch == old_string[match_count])
		{
			match_count++;
			if(match_count < old_string.length())
				continue;
		}
		if(match_count == old_string.length())
		{
			//cout << "Full Match!\n";
			ss.matched_search_string();
		}else if (match_count > 0)
		{
			ss.found_partial_match(ch, match_count);
		}else
		{
			//cout << "putting " << ch << endl;
			ss.put(ch);
		}
	
		match_count = 0;

	} // end of while
	cout << "Ending queue size: ";
	ss.print_queue_size();
	return 0;
}	
