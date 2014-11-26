#ifndef REPLACE_H
#define REPLACE_H
#include <fstream>
#include "TrackingDeque.h"

class Replace
{
	public:
		Replace(char* file_name);
		~Replace();
		void replace(string old_s, string new_s);
	private:
		fstream file_stream;
		int get_pos;
		int put_pos;
		int match_pos;
		TrackingDeque<char> *queue;
		char *filename;
		string old_string;
		string new_string;
		int substitutions;

};


#endif
