#include "Replace.h"
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

Replace::Replace(char* file_name) : filename(file_name), get_pos(0), put_pos(0), match_pos(0), queue(new TrackingDeque<char>()), substitutions(0)
{
	file_stream.open(file_name, ios_base::in | ios_base::out);
}

Replace::~Replace()
{
	delete queue;
	file_stream.close();
	if(old_string.size() > new_string.size())
	{
		cout << "truncating file" << endl;
		int return_val;
		return_val = truncate(filename, put_pos);
	}
}

void Replace::replace(string old_s, string new_s)
{
	old_string = old_s;
	new_string = new_s;
	char cur_char;
	get_pos = 0;
	match_pos = 0;
	put_pos = 0;

	do
	{		
		if(queue->size() > 0)
		{	
			if(file_stream.eof() && queue->size() == 1)
			{
				break;
			}
			cur_char = queue->at(0);
			queue->pop_front();
			//cout << "Just Read from queue: " << cur_char << endl;
			if(!file_stream.eof())
			{
				file_stream.seekg(get_pos);
				char push = file_stream.get();
				//cout << "Pushing " << push << "from position " << get_pos<<endl;
				queue->push_back(push);
				get_pos++;
			}			
		}else
		{
			file_stream.seekg(get_pos);
			file_stream.get(cur_char);
			if(file_stream.eof())
				break;
			//cout << "Just Read: " << cur_char << " at position(get) = " << get_pos << endl;	
			get_pos++;
		}
			
		if(match_pos > 0 && (cur_char != old_s[match_pos]))
		{		
			//cout << "current char = " << cur_char << endl;
			int add_to_match_pos = 0;
			int index = 0;
			int print_these = match_pos;
			for(int i = 0; i < match_pos; i++)
			{
				if(old_s[i] == old_s[index] && i != 0)
				{
					//cout << "match at counter " << i << endl;
					print_these = i;
					add_to_match_pos++;
					index++;
				}else
				{
					add_to_match_pos = 0;
					index = 0;
					print_these = match_pos;
				}						
			}
			for(int j = 0; j < print_these; j++)
			{
				file_stream.seekp(put_pos);				
				file_stream.put(old_s[j]);
				put_pos++;
			}
			//cout << "Match pos = " << add_to_match_pos << endl;
			match_pos = add_to_match_pos;
		}

		//matched a single char
		if(cur_char == old_s[match_pos])
		{
			match_pos++; 	//increment match position
			
			if(match_pos == old_s.size()) //matched completely
			{
				if(old_s.size() == new_s.size())
				{
					for(int i = 0; i < new_s.size(); i++)
					{
						file_stream.seekp(put_pos);
						file_stream.put(new_s[i]);
						put_pos++;	
					}
				}else if(old_s.size() > new_s.size())
				{
					for(int i = 0; i < new_s.size(); i++)
					{
						file_stream.seekp(put_pos);
						file_stream.put(new_s[i]);
						put_pos++;	
					}
					
				}else if(old_s.size() < new_s.size())
				{		
					for(int i = 0; i < (new_s.size()-old_s.size()); i++)
					{
						if(!file_stream.eof())
						{
							file_stream.seekg(get_pos);
							char check = file_stream.get();
							//cout << "Read " << check << " at position " << get_pos << endl;
							get_pos++;
							
							queue->push_back(check);
							if(file_stream.eof())
							{
								break;  //if we've reached EOF, get out.
							}
							
						}
					}
					if(file_stream.eof())
					{
						file_stream.clear(); //clear error flags so we can print
						file_stream.seekp(put_pos);
						for(int i = 0; i < new_s.size(); i++)
						{
							file_stream.put(new_s[i]);
							put_pos++;
						}
						file_stream.setstate(ios::eofbit); //reset eof flag.
					}else
					{
						file_stream.seekp(put_pos);
						for(int i = 0; i < new_s.size(); i++)
						{
							file_stream.put(new_s[i]);
							put_pos++;
						}
					}
				}
				substitutions++;
				match_pos = 0; //reset match position after we replace.
			}
		}else
		{	
			//NEED TO CHECK cur_char STILL FOR MATCH
			
				//queue->push_back(cur_char);
			if(cur_char != EOF) // || cur_char != '\n'
			{
				if(!file_stream.eof())
				{
					file_stream.seekp(put_pos);
					//cout << "putting " << cur_char << " at position: "<< put_pos << endl;
					file_stream.put(cur_char);
					put_pos++;
				}else
				{
					file_stream.clear();
					file_stream.seekp(put_pos);
					//cout << "putting " << cur_char << " at position: "<< put_pos << endl;
					file_stream.put(cur_char);
					put_pos++;
					file_stream.setstate(ios::eofbit);
				}
			}
			
		}
		
		/*cout << "STACK:" << endl;
		//print stack - DEBUGGING
		for(int i =0; i < queue->size(); i++)
			cout << "Element " << i << ": " << queue->at(i) << endl;
		*/


		//if our put_pos ever gets over get_pos, we need to stop an infinite loop.
		/*if(put_pos > get_pos)
		{
			cout << "INFINITE LOOP WARNING\n";
			//break;
		}
		if(cur_char == '\n' || cur_char == EOF)
		{
			break;
		}*/

		
	}while(cur_char != EOF);
}





