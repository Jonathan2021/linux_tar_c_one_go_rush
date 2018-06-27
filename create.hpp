#ifndef _CREATE_HPP_
#define _CREATE_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "header.hpp"

using namespace std;
void create(int argc, char* argv[], int position);
void read_directory(string cur_dir, vector<string>& v);
void make_header(const char* filename, Header* header);
off_t add_at_end(off_t size);
#endif
