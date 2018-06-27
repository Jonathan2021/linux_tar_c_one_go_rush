#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include "extract.hpp"
using namespace std;

void _compare(string file_name, string& tar_content, int i)
{
	struct stat buff;
       	if(stat(file_name.c_str(), &buff) == 0)
        {
        	if(strcmp(to_string((unsigned long long)buff.st_mode).c_str(), to_string(oct_to_dec(clean_content(&tar_content[i+100],8))).c_str()))
                {
                	cout << "in " << file_name << ", file mode changed" << endl;
                }
               	if(strcmp(to_string((unsigned long long)buff.st_size).c_str(), to_string(oct_to_dec(clean_content(&tar_content[i + 124], 12))).c_str()))
                {
     	           	cout << file_name << "  isn't the same size" << endl;
                }
               	if(strcmp(to_string((unsigned long long)buff.st_uid).c_str(), to_string(oct_to_dec(clean_content(&tar_content[i+108],8))).c_str()))
                {
                	cout << "in " << file_name << ", owner user id changed" << endl;
                }
                if(strcmp(to_string((unsigned long long)buff.st_mtime).c_str(), to_string(oct_to_dec(clean_content(&tar_content[i+136],12))).c_str()))
                {
                	cout << file_name << "'s last modification time changed" << endl;       
                }
        }
	else
	{
		cout << file_name << " doesn't exist anymore" << endl;
	}
}
		
		


void compare(int argc, char* argv[], int pos)
{
	string tar_content = "";
	int done = 0;
	get_tar(argv[pos], tar_content);
        size_t tar_size = get_size(argv[pos]) - 1024;
	if ( done < argc - (pos+1))
	{
		for(size_t i =0; i<tar_size && done < argc -(pos+1);)
		{
			string file_name = clean_content(&tar_content[i],100);
			size_t file_size = oct_to_dec(clean_content(&tar_content[i + 124], 12));
			if(file_in_argv(file_name, argc, argv))
			{
				_compare(file_name, tar_content, i);
			}
			 i += 512;
                        i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));
		}
	}
	else
	{
		for(size_t i = 0 ; i<tar_size;)
		{
			 string file_name = clean_content(&tar_content[i],100);
                        size_t file_size = oct_to_dec(clean_content(&tar_content[i + 124], 12));
			_compare(file_name, tar_content, i);
			 i += 512;
                        i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));

		}
	}
}
