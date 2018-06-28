#include <string>
#include <fstream>
#include <iostream>
#include "create.hpp"
#include "header.hpp"
#include "extract.hpp"
#include <sys/stat.h>
#include <vector>

using namespace std;

void append(int argc, char* argv[], int pos)
{
	size_t in_size;
	string cur_argv;
	vector<string> v;
	string cur_s = "";
	string res = "";
	get_tar(argv[pos], cur_s);
	in_size = get_size(argv[pos]);
	res+= cur_s.substr(0,in_size-1024);
	ofstream out_file;
	out_file.open(argv[pos], ios::trunc);
	if(out_file)
	{
		out_file.write(res.c_str(), res.length());
		out_file.close();
		for (int i = pos+1 ; i < argc ; ++i)
		{
			cur_argv = string(argv[i]);
			if (argv[i][(cur_argv.size()-1)] == '/')
			{
				v.clear();
				read_directory(cur_argv,  v);
				for(size_t j =0 ; j< v.size(); ++j)
                                {
                                	write_file(argv[pos], v.at(j).c_str());
                                }

			}
			else
			{
				write_file(argv[pos], argv[i]);
			}
		}
		out_file.open(argv[pos], ios::app);
		if(out_file)
		{
			for(size_t j = 0; j<1024; ++j)
        		{
                		out_file << '\0';
        		}
        	}
	}
	out_file.close();

}


