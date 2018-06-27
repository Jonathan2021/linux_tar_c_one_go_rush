#ifndef _EXTRACT_HPP_
#define _EXTRACT_HPP_

#include <iostream>
#include <string>
using namespace std;

size_t get_size(char* filename);
void get_tar(char filename[], string& str);
void extract(int argc, char* argv[], int position);

#endif
