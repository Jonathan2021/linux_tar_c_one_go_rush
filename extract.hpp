#ifndef _EXTRACT_HPP_
#define _EXTRACT_HPP_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

size_t get_size(char* filename);
void get_tar(char filename[], string& str);
void extract(int argc, char* argv[], int position);
string clean_content(char* cur_char, size_t stop);
size_t oct_to_dec(string oct);
int file_in_argv(string file_name, int argc, char* argv[]);
size_t get_directories(string file_name, size_t pos, vector<string>& directories);
#endif
