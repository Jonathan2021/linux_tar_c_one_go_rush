#ifndef _HEADER_HPP_
#define _HEADER_HPP_	
#include <iostream>
using namespace std;

struct Header{
	char file_name[100];
	char file_mod[8];
	char owner_user_id[8];
	char group_user_id[8];
	char file_size[12]; //octal
	char last_mod_time[12]; //Unix time format (octal)
	char checksum[8];
	char link_indicator[1];
	char name_link[100];	
	char ustar_indicator[6];
	char ustar_version[2];
	char owner_name[32];
	char group_name[32];
	char device_major[8];
	char device_minor[8];
	char prefix[155];
	char inutile[12];
	off_t size;
};
#endif
