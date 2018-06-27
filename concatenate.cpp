#include "extract.hpp"
#include <string>
#include <fstream>
using namespace std;

void concatenate(int argc, char* argv[], int pos)
{
	size_t in_size;
	string cur_s = "";
	string res = "";
	get_tar(argv[pos], cur_s);
	for(int i = pos; i<argc; ++i)
	{
		in_size = get_size(argv[i]);
		cur_s.clear();
		get_tar(argv[i], cur_s);
		res += cur_s.substr(0, in_size-1024);
	}
	for(size_t i = 0; i<1024; ++i)
	{
		res += '\0';
	}
	ofstream out_file;
	out_file.open(argv[pos], ios::trunc);
	if(out_file)
	{
		out_file.write(res.c_str(),res.length());
	}
}
