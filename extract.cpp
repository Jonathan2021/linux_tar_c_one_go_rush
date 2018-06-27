#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/stat.h>

using namespace std;
/*
void copyFile(string src, string dst){
	ifstream src_file;
	src_file.open(src);
	ofstream dst_file;
	dst_file.open(dst);
	char c;
	while (src_file.get(c)){
		dst_file.put(c);
		if (src_file.eof())
			break;
	}
	src_file.close();
	dst_file.close();
}
*/

void get_tar(char filename[], string& str){
    str.clear();
    ifstream infile;
	infile.open(filename);
    if (infile)
    {
	char c;
      while (infile.get(c))
      {
        str += c;
      }
      infile.close();
    }
}
string clean_content(char* cur_char, size_t stop){
    string clean = "";
    for(size_t n = 0; n < stop && *cur_char != '\0';++n){
        clean += *(cur_char++);
    }
    return clean;
}

size_t get_size(char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

int char_to_int(char c){
	return (c>= '0' && c<='9') ? c - 48 : 0;
}

size_t oct_to_dec(string oct){
    	//cout << "oct: " << oct << endl;
	size_t dec = 0;
    size_t power = 1;
    for (int i = oct.length() - 1; i >= 0; --i){
        dec += power * char_to_int(oct[i]);
        power *= 8;
    }
	//cout << "dec : " << dec << endl;
    return dec;
}


int file_in_argv(string file_name, int argc, char* argv[])
{
	for(int i = 1; i<argc; ++i)
	{
		if (strcmp(argv[i], file_name.c_str()) == 0)
		{
			return i;
		}
	}
	return 0;
} 
size_t get_directories(string file_name, size_t pos, vector<string>& directories)
{
	for(size_t i = pos + 1; i<file_name.size(); ++i)
	{
		if (file_name[i] == '/')
		{
			directories.push_back(file_name.substr(0, (i + 1)));
			pos = i;
			return get_directories(file_name, pos, directories);
		}
	}
	return pos;
}
int dir_exists(string name)
{
	struct stat sb;
	if (stat(name.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return 1;
	}
	return 0;
}
void make_file(string file_name, string tar_content, size_t file_number, size_t file_size)
{
	ofstream outfile;
	outfile.open(file_name.c_str(), ios::trunc);
	if(outfile)
	{	
		outfile.write(&tar_content[file_number+512], file_size);
	}
	outfile.close();
}
void extract(int argc, char* argv[], int position){
    	size_t pos;
	string tar_content = "";
    	get_tar(argv[position], tar_content);
	vector<string> directories;
	int done = 0;
    	size_t tarsize = get_size(argv[position]) - 1024;
    	for(size_t file_number =0 ; file_number<tarsize;)
	{
	//	cout << "file number : " << file_number << endl;
	//	cout << tar_content[file_number] << tar_content[file_number +1] << endl;
        	string file_name = clean_content(&tar_content[file_number], 100);
	//	cout << "file name: " << file_name << endl;
	//	size_t file_size = (tar_content[file_number + 156] == '5') ? 0 : oct_to_dec(clean_content(&tar_content[file_number + 124], 12));
		size_t file_size = oct_to_dec(clean_content(&tar_content[file_number + 124], 12));

		if (done<argc - (position + 1 ))
		{
			if (file_in_argv(file_name, argc, argv))
			{
				directories.clear();
				pos = get_directories(file_name, 0, directories);
				for (size_t i = 0 ; i<directories.size(); ++i)
				{
					if(!dir_exists(directories.at(i)))
					{
						 mkdir(directories.at(i).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					}
				}
				if(pos<(file_name.size()-1))
				{
					make_file(file_name,tar_content, file_number, file_size);
				}
				done +=1;
			}
		}
		else if (argc<= (position + 1))
		{
			if(file_name[file_name.size()-1] == '/')
			{
				if(!dir_exists(file_name))
				{
					 mkdir(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);                      
				}
			}
			else
			{
				make_file(file_name, tar_content, file_number, file_size);
			}
		}
			file_number += 512;
	    		file_number += (((file_size % 512) == 0)? file_size : file_size + 512 - (file_size % 512));
	}
}
