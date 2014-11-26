#include "Buffered_File.h"
using namespace std;


Buffered_File::Buffered_File(char* filename)
{
	open(filename);
}

Buffered_File::~Buffered_File()
{
	close();
}

int Buffered_File::get(char &ch, int &get_pos, int &replacements)
{
	seekg(get_pos);
	if(queue.size() > 0 && replacements > 0) //replacements is a var for when new_length > old_length to tell the queue to keep a buffer of new_length - old_length chars
	{
		ch = queue[0];
		queue.pop_front();
		char temp = fstream::get();
		get_pos++;
		if(bad() && (queue.at(queue.size()-1) == EOF))
		{
			//cout << "bad and eof on queue\n";
			clear();
		}else if(bad())
		{
			//cout << "BAD" << endl;
			clear();
			queue.push_back(EOF);
		}else
		{
			if(temp != EOF)
			{
				//cout << "Taking " << ch << " from queue (get) get_pos = " << get_pos << " and pushing " << temp << " from pos " << get_pos - 1 << endl;
				queue.push_back(temp);
			}
		}
	}else if(queue.size() > 0) //if something is on the queue, use it for ch.
	{
		ch = queue[0];
		//cout << "Taking " << ch << " from queue (get) get_pos = " << get_pos << endl;
		queue.pop_front();
		return 0;
	}else
	{
		ch = fstream::get();
		//cout << "getting " << ch << " from get_pos " << get_pos << endl;
		get_pos++;
		if(bad())
		{
			clear();
			ch = EOF;
		}
		
		return ch;
	}
}

int Buffered_File::get_and_push(int &get_pos, int &gets_to_push)
{
	seekg(get_pos);
	char ch;
	ch = fstream::get();
	//if(queue.size() > 0)
		//cout << "Last element in queue = " << queue.at(queue.size()-1) << endl;
	if(bad() && (queue.at(queue.size()-1) == EOF))
	{
		//cout << "bad and eof on queue\n";
		clear();
	}else if(bad())
	{
		//cout << "BAD\n";
		clear();
		queue.push_back(EOF);
	}else
	{
		if(ch != EOF)
		{
			//cout << "get and push " << ch << " from pos " << get_pos << endl;
			queue.push_back(ch);
		}
	}
	get_pos++;
	gets_to_push--;
}

void Buffered_File::put(int &put_pos, char &ch)
{
	clear();
	seekp(put_pos);
	//cout << "Putting " << ch << " at pos " << put_pos << endl;;
	(*this).fstream::put(ch);
	put_pos++;
}

void Buffered_File::queue_print()
{
	cout << "Printing Queue:\n";
	for(int i =0; i < queue.size(); i++)
		cout << queue.at(i) << endl;
	cout << "Done printing queue\n";
}

