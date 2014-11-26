#include "StreamSource.h"
#include <unistd.h>
#include <sys/types.h>
using namespace std;

StreamSource::StreamSource(char *filename, string old_s, string new_s) : currently_replacing(false), old_string(old_s), new_string(new_s), bad_match_iter(0), bf(new Buffered_File(filename)), get_pos(0), put_pos(0), num_chars_to_write(0), num_chars_to_write_bad_match(0), gets_to_push(0), file(filename), replacements(0)
{

}

StreamSource::~StreamSource()
{
	if(old_string.size() > new_string.size())
	{
		cout << "truncating file" << endl;
		int return_val;
		return_val = truncate(file, put_pos);
	}
	delete bf;
}


bool StreamSource::replacing()
{
	return currently_replacing;
}

void StreamSource::matched_search_string()
{
	currently_replacing = true;
	num_chars_to_write = new_string.length();
	if(new_string.length() > old_string.length())
	{
		gets_to_push += new_string.length()-old_string.length();
		replacements++;
		while(gets_to_push > 0)
		{
			bf->get_and_push(get_pos, gets_to_push);
		}
	}
	
}

void StreamSource::found_partial_match(char ch, int match_count)
{
	if(match_count > num_chars_to_write_bad_match)
	{
		num_chars_to_write_bad_match = match_count;
		bad_match_iter = 0;
		//cout << "pushing " << ch << " onto the queue\n";
		bf->queue.push_back(ch);
	}else
	{
		for(int i = 0; i < match_count; i++)
		{
			put(old_string[i]);
		}
		put(ch);
	}
}

int StreamSource::get(char &ch)
{	
	if(num_chars_to_write > 0)
	{
		currently_replacing = true;
		ch = new_string[new_string.length() - num_chars_to_write];
		num_chars_to_write--;
		return 0;
	}else if(num_chars_to_write_bad_match > 0)
	{
		if(bad_match_iter == 0) //if it's a partial match, always output the first char without attempting to match it again(this prevents and endless loop).
			currently_replacing = true;
		else //after the first is output, look for substring matches.
			currently_replacing = false;

		ch = old_string[bad_match_iter];
		bad_match_iter++;
		if(bad_match_iter == num_chars_to_write_bad_match)
		{
			num_chars_to_write_bad_match = 0;
		}
		return 0;
	}else
	{
		currently_replacing = false;
		int ret;
		ret = bf->get(ch, get_pos, replacements); 
		return ret;
	}
}

void StreamSource::put(char &ch)
{
	bf->put(put_pos, ch);
}

bool StreamSource::eof()
{
	return bf->eof();
}

void StreamSource::print_queue_size()
{
	cout << bf->queue.size() << endl;
	bf->queue_print();
}

