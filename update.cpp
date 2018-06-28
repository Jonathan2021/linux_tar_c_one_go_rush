#include <iostream>
#include <algorithm>
#include <string>
#include "list.hpp"
#include "extract.hpp"
#include "append.hpp"
#include <vector>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>


using namespace std;

void update(int argc, char* argv[], int pos)
{
	cout << "je rentre ds update" <<endl;
	string tar_content = "";
        get_tar(argv[pos], tar_content);
        vector<string> list;
        size_t tarsize = get_size(argv[pos]) - 1024;
        size_t file_size;
        for(size_t i = 0 ; i<tarsize;)
        {
                string file_name = clean_content(&tar_content[i], 100);
                if (file_in_argv(file_name, argc, argv))
                {
			if(file_name[file_name.length()-1] == '/')
			{
				cout << "relou un dossier : " << file_name << endl;
                        	if(!(find(list.begin(), list.end(), file_name) != list.end()))
                                	list.push_back(file_name);
				list_directory(file_name, tar_content, tarsize, list);
			}
			else
			{
				cout << "fichier normal : " << file_name<< endl;
				 if(!(find(list.begin(), list.end(), file_name) != list.end()))
                                        list.push_back(file_name);
			}
                }
                file_size = oct_to_dec(clean_content(&tar_content[i + 124], 12));
                i += 512;
                 i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));
        }
	struct stat buff;
	size_t j = 0;
        for (size_t i = 0; i< tarsize && j < list.size();)
        {
		cout << "je rentre dans la deuxieme boucle" << endl;
         	string file_name = clean_content(&tar_content[i], 100);
		cout << "vect size : " << list.size() << endl;
		if(find(list.begin(), list.end(), file_name) != list.end() && file_name[file_name.length()-1] != '/')
			{
				cout << "a update :" << file_name << endl;
			 	if(stat(file_name.c_str(), &buff) == 0)
        			{
				 	if(strcmp(to_string((unsigned long long)buff.st_mtime).c_str(), to_string(oct_to_dec(clean_content(&tar_content[i+136],12))).c_str()))
   			         	{
						append(argv[pos], file_name);
						j++;
                			}

                		}

			}
		file_size = oct_to_dec(clean_content(&tar_content[i + 124], 12));
		i += 512;
                 i += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));      
	}
}
