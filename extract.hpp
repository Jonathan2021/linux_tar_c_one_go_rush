#ifndef _TAR_E_HPP
#define _TAR_E_HPP

#include <iostream>
#include <string>


void copyFile(std::string src, std::string dst);
size_t getFileSize(std::string filename);
void getContent(std::string filename, std::string& str);
size_t octalToDecimal(std::string nombre);
std::string removeZeros(char* str, size_t siz);
int charToInt(char c);
std::string archiveContains(std::string name, int argc, char* argv[]);
void extract(std::string tarname, int argc, char* argv[], bool verbose);

#endif
