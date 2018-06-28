#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <iostream>
#include <vector>
using namespace std;

void list_directory(string file_name, string& content, size_t size, vector<string>& list);
void list(int argc, char* argv[], int pos); 

#endif
