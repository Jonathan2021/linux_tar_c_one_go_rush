#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/stat.h>

using namespace std;

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

size_t getFileSize(string filename){
    streampos begin_pos,end_pos;
    ifstream file_s (filename, ios::binary);
    begin_pos = file_s.tellg();
    file_s.seekg (0, ios::end);
    end_pos = file_s.tellg();
    file_s.close();
    return end_pos - begin_pos;
}

void getContent(string filename, string& str){
    str.clear();
    string line;
    ifstream file_s (filename);
    if (file_s.is_open())
    {
      while ( getline (file_s,line) )
      {
        str += line + (file_s.eof() ? '\0' : '\n');
      }
      file_s.close();
    }
}

int charToInt(char c){
    switch (c){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
    return 0;
}

size_t octalToDecimal(string nombre){
    size_t result = 0;
    size_t iter = 1;
    for (int i = nombre.size() - 1; i >= 0; i--){
        result += iter * charToInt(nombre[i]);
        iter *= 8;
    }
    return result;
}

string removeZeros(char* str, size_t siz){
    size_t n = 0;
    string result = "";
    while (n < siz && *str != '\0'){
        result += *(str++);
    }
    return result;
}

string archiveContains(string name, int argc, char* argv[]){
    //a tafer. verifier si dossier, blabla... elaborer une meilleure methode
    int i = 0;
    while (i < argc && strcmp(argv[3 + i], name.c_str()) != 0 ){
        string current_string = (string)argv[3 + i];
        if (current_string.find("/") == current_string.size() - 1 && name.find(current_string) != std::string::npos) return current_string;
        i++;
    }
    return (i != argc ? name : "");
}

void extract(string tarname, int argc, char* argv[], bool verbose){

    string content = "";
    getContent(tarname, content);
    size_t iter = 0;
    size_t tarsize = getFileSize(tarname) - 1024;
    while (iter < tarsize){
        string filename = removeZeros(&content[iter], 100);
	size_t filesize = octalToDecimal(removeZeros(&content[iter + 124], 12));
	string filetocreate = archiveContains(filename, argc, argv);
        if (!argc || (argc && filetocreate.length())){
            if (!filesize){
                if (verbose) cout << filename << endl;
                if (mkdir(filename.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1){
                    cerr << "error extracting directory " << filename << endl;
                }
            } else {
                ofstream fichier(argc ? filetocreate : filename, ios::out | ios::trunc);
                if(fichier) {
                    fichier << removeZeros(&content[iter + 512], filesize);
                    fichier.close();
                }
                else cerr << "error: " << filetocreate << endl;
            }
        }
        iter += 512;
	    iter += (((filesize % 512) == 0)? filesize : filesize + 512 - (filesize % 512));
    }

}
