#ifndef STREAMSOURCE_H
#define STREAMSOURCE_H
#include <iostream>
#include <string>
#include "Buffered_File.h"
using namespace std;

class StreamSource
{
	public:
	StreamSource(char *filename,string old_s,string new_s);
	~StreamSource();
	bool replacing();
	void matched_search_string();
	void found_partial_match(char ch, int match_count);
	int get(char &ch);
	void put(char &ch);
	bool eof();
	void print_queue_size();
	private:
	Buffered_File *bf;
	int get_pos;
	int put_pos;
	int num_chars_to_write_bad_match;
	int num_chars_to_write;
	bool currently_replacing;
	string old_string;
	string new_string;
	int bad_match_iter;
	int gets_to_push;
	char *file;
	int replacements;
};

#endif
