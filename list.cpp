#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include "extract.hpp"

using namespace std;
void list_directory(string file_name, string& content, size_t size, vector<string>& list)
{
	size_t file_size;
	string cur_name;
	size_t len = file_name.length();
	size_t cur_len;
	for (size_t i = 0; i<size;)
	{
		 cur_name = clean_content(&content[i], 100);
		cur_len = cur_name.length();
		if (cur_len>len)
		{
			if(!strcmp(cur_name.c_str(), (file_name+cur_name.substr(len, -1)).c_str()))	
			{
				if(!(find(list.begin(), list.end(), cur_name) != list.end()))
                                	list.push_back(cur_name);
			}
		}
		 file_size = oct_to_dec(clean_content(&content[i + 124], 12));
                i += 512;
                 i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));

	}
}

void list(int argc, char* argv[], int pos)
{
	string tar_content = "";
        get_tar(argv[pos], tar_content);
	vector<string> list;
	size_t tarsize = get_size(argv[pos]) - 1024;
	int done = 0;
	size_t file_size;
	;
	for(size_t i = 0 ; i<tarsize;)
	{
		string file_name = clean_content(&tar_content[i], 100);
		if (argc<= (pos+1))
		{
			if(!(find(list.begin(), list.end(), file_name) != list.end()))
				list.push_back(file_name);
		}
		else if (done< argc - (pos + 1 ))
		{
			if (file_in_argv(file_name, argc, argv))
			{
				if (file_name[file_name.length()-1] == '/')
				{	
					if(!(find(list.begin(), list.end(), file_name) != list.end()))
                                        	list.push_back(file_name);
					list_directory(file_name, tar_content, tarsize, list);
				}
				else
				{
					if(!(find(list.begin(), list.end(), file_name) != list.end()))
                                		list.push_back(file_name);
				}
				done ++;
				if (done>= argc - (pos + 1 ))
					break;
			}
		}
		file_size = oct_to_dec(clean_content(&tar_content[i + 124], 12));
		i += 512;
                 i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));
	}
	for (size_t i = 0; i< list.size(); i++)
	{
		cout << list.at(i) << endl;
	}
}
