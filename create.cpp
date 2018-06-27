//#include <filesystem> //c++17
#include <iterator>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <grp.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "header.hpp"
#include <vector>
using namespace std;

void initiate_header(Header* header)
{
	memset((void*) header, '\0', 512);
}

void add_name(Header* header, string name)
{
	if (name == "" || name[0] == 0 || name.length()>100)
		cerr << "file name/path too long" << endl;
	else
		strcpy(header->file_name, name.c_str());
}

void add_file_mode(Header* header, struct stat* buff)
{
	  if(buff->st_mode & S_IFDIR)
                 sprintf(header->file_mod,"%07o",0775);
        if(buff->st_mode & S_IFREG)
                sprintf(header->file_mod,"%07o",0644);
}

void add_user_id(Header* header, struct stat* buff)
{
	uid_t id = buff->st_uid;
	sprintf(header->owner_user_id, "%07o", id);
}

void add_group_id(Header* header, struct stat* buff)
{
	gid_t id = buff->st_gid;
	sprintf(header->group_user_id, "%07o", id);
}

void add_size(Header* header, struct stat* buff)
{
	if(buff->st_mode & S_IFDIR)
	{
              	sprintf(header->file_size,"%011o", 0);
	}
        else if(buff->st_mode & S_IFREG)
	{
		off_t size = buff->st_size;
		header->size = size;
		sprintf(header->file_size,"%011o", (unsigned int)size);
	}
}



void add_mod_time(Header* header, struct stat* buff)
{
	time_t time = buff->st_mtime;
	sprintf(header->last_mod_time,"%011lo", time);
}

void checksum(Header* header)
{
	unsigned int sum = 0;
	char* p = (char*) header;
	char* stop = p + 512;
	for (; p<header->checksum; ++p)
		sum += *p & 0xff;
	for (size_t i = 0; i<8; ++i)
	{
		sum += ' ';
		++p;
	}	
	for (; p<stop; ++p)
		sum += *p & 0xff;
	sprintf(header->checksum, "%06o", sum);
	header->checksum[6] = '\0';
	header->checksum[7] = ' ';
}

void typeflag(Header* header, struct stat* buff) //stat* buff)
{
	if(buff->st_mode & S_IFDIR)
		header->link_indicator[0]='5';
	if(buff->st_mode & S_IFREG) 
		header->link_indicator[0] = '0';
}

void ustar_indicator(Header* header)
{
	strcpy(header->ustar_indicator, "ustar ");
}

void ustar_version(Header* header)
{
	strcpy(header->ustar_version, " ");
}
void get_owner_name(Header* header)
{
	strcpy(header->owner_name, getenv("USER"));
}

void get_goup_name(Header* header, struct stat* buf)
{
	struct group *grp;
	grp = getgrgid(buf->st_gid);
	strcpy(header->group_name, grp->gr_name);
}

void make_header(const char* filename, Header* header)
{
	struct stat buff;
	stat(filename, &buff);
	struct stat* cur_stat = &buff;
	initiate_header(header);	
	add_name(header, string(filename));
	add_file_mode(header, cur_stat);		
	add_user_id(header, cur_stat);
	add_group_id(header, cur_stat);
	add_size(header, cur_stat);
	add_mod_time(header, cur_stat);
	typeflag(header, cur_stat);
	ustar_indicator(header);
	ustar_version(header);
	get_owner_name(header);
	get_goup_name(header, cur_stat);
	checksum(header);
}

off_t add_at_end(off_t size)
{
	off_t re = 512 - (size%512);
	if (re == 512)
		re = 0;
	return re;	
}

void write_file(char* out_file, const char* in_file)
{
	ifstream infile;
	infile.open(in_file);
	ofstream outfile;
	outfile.open(out_file, ios::app);
	if(infile)
	{
		Header h = Header();
		Header* header = &h;
		make_header(in_file, header);
		ofstream outfile;
	        outfile.open(out_file, ios::app);
		outfile.write((char *)header, 512);
		char c;
		while(infile.get(c))
		{
			outfile << c;
		}
		off_t complete = add_at_end(h.size);
		for (off_t i = 0; i<complete; ++i)
			outfile << '\0';
		infile.close();
		outfile.close();	
	}	
}
void read_directory(string cur_dir, vector<string>& v)
{
	DIR* dirp= opendir(cur_dir.c_str());
	struct dirent* dp;
	v.push_back(cur_dir);
	if (dirp == NULL)
	{
		cerr << "opendir: Path doesn't exist or couldn't be read" << endl;
	}
	string add_name;
	while ((dp = readdir(dirp)) != NULL)
	{
		add_name = string(dp->d_name);
		if( add_name!= "." && add_name != "..")
		{
			if(dp->d_type == DT_DIR)
			{
				read_directory((cur_dir + add_name + "/"), v);
			}
			else
			{
				v.push_back(cur_dir +  add_name);
			}
		}
	}
	closedir(dirp);
}

void create(int argc, char** argv, int pos)
{

		string file_argv;
		vector<string> v;
		for(int i = pos+1; i< argc; ++i)
		{ 
			v.clear();
			file_argv = string(argv[i]);
			if(argv[i][(file_argv.size()-1)] == '/' || (file_argv.size() == 1 && argv[i][0]== '.'))
			{
				read_directory(file_argv, v);
				for(size_t j =0 ; j< v.size(); ++j)
				{
					write_file(argv[pos], v.at(j).c_str());
				}
					 
			}
			else
				write_file(argv[pos], argv[i]);
		}
		ofstream outfile;
		outfile.open(argv[pos], ios::app);
		for(size_t i = 0 ; i< 1024; ++i)
		{
			outfile << '\0';
		}	
		outfile.close();
}

