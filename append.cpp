#include <string>
#include <fstream>
#include <iostream>
#include "create.hpp"
#include "header.hpp"
#include "extract.hpp"
#include <sys/stat.h>

using namespace std;

void append(int argc, char* argv[], int pos)
{
	size_t in_size;
	char c;
	string cur_s = "";
	string res = "";
	get_tar(argv[pos], cur_s);
	in_size = get_size(argv[pos]);
	res+= cur_s.substr(0,in_size-1024);
	Header h;
	Header* header;
	ofstream out_file;
	out_file.open(argv[pos], ios::trunc);
	if(out_file)
	{
		out_file.write(res.c_str(), res.length());
		for (int i = pos+1 ; i < argc ; ++i)
		{
			ifstream in_file;
        		in_file.open(argv[i]);
        		if(in_file)
        		{
                		h = Header();
                		header = &h; 
                		make_header(argv[i], header);
                		out_file.write((char *)header, 512);
                		while(in_file.get(c))
                		{
                        		out_file << c;
                		}
                		off_t complete = add_at_end(h.size);
                		for (off_t i = 0; i<complete; ++i)
                        		out_file << '\0';
                		in_file.close();
			}
		}
		for(size_t j = 0; j<1024; ++j)
        	{
                	out_file << '\0';
        	}

        }
	out_file.close();
}


