#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "create.hpp"
#include "extract.hpp"
#include "concatenate.hpp"
#include "append.hpp"
#include <stdio.h>
#include <string.h>

using namespace std;

void version()
{
	cout << "bsdtar 2.8.3 - libarchive 2.8.3" << endl;
}
void help()
{
	cout << "tar(bsdtar): manipulate archive files" << endl;
}
void missing()
{
	 cout <<"tar: Must specify one of -c, -r, -t, -u, -x"<<endl;
}

int main (int argc, char *argv[])
{
if (argc >1) {
	int extract_bool = 0;
	int create_bool = 0;
	int catenate_bool = 0;
	int append_bool = 0;
	int i = 1;
	int wait_f_cat = 0;
	int wait_f_ex = 0;
	int wait_f_creat = 0;
	int wait_f_app = 0;
	while (i<argc && argv[i][0] == '-')
	{
		
		if (!strcmp(argv[i], "--version")) 
		{
			version();
		}
		else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-?")) 
		{
			help();
		}
		else if (!strcmp(argv[i], "-rf"))
		{
			append_bool = 1;
		}
		else if (!strcmp(argv[i], "-Af"))
		{
			catenate_bool = 1;
		}
		else if (!strcmp(argv[i], "--catenate") || !strcmp(argv[i], "-A") || !strcmp(argv[i], "--concatenate"))
		{
			wait_f_cat = 1;	
		}
		else if(!strcmp(argv[i], "--append") || !strcmp(argv[i], "-r"))
		{
			wait_f_app = 1;
		}
		else if (!strcmp(argv[i], "-xf"))
		{
			extract_bool = 1;
		}
		else if	(!strcmp(argv[i], "--extract") || !strcmp(argv[i], "-x") || !strcmp(argv[i], "--get"))
		{
			wait_f_ex = 1;
		}

		else if (!strcmp(argv[i], "-cf"))
		{
			create_bool = 1;	
		}
		else if(!strcmp(argv[i], "--create") || !strcmp(argv[i], "-c"))
		{
			wait_f_creat = 1;
		}
		else if (!strcmp(argv[i], "-f"))
		{
			if(wait_f_ex)
			{
				extract_bool = 1;
			}
			if (wait_f_creat)
			{
				create_bool = 1;
			}
			if(wait_f_cat)
			{
				catenate_bool = 1;
			}
			if(wait_f_app)
			{
				append_bool = 1;
			}
		}
		else 
		{
			missing();
		}
		++i;
	}
	if (i<argc)
	{
		if (catenate_bool + extract_bool + create_bool + append_bool> 1)
		{
			cout <<"casting incompatible actions" << endl;
		}
		else if(extract_bool)
		{
			extract(argc, argv, i);
		}
		else if (create_bool)
			create(argc, argv, i);
		else if (catenate_bool && i+1<argc)
		{
			concatenate(argc, argv, i);
		}
		else if (append_bool && i+1 < argc)
		{
			append(argc, argv, i);
		}
			
	}
}
return 0;
}

