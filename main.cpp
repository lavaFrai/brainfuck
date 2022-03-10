#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <filesystem>
#include "consts.h"
#include "vm.h"

using namespace std;

bool contents(vector<string> array, const string& value)
{
    __gnu_cxx::__normal_iterator<std::basic_string<char> *, std::vector<std::basic_string<char>>> it = find(array.begin(), array.end(), value);
    if (it == array.end())
        return false;
    return true;
}

long long filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


int main(int argc, char** argv) {
    vector<string>args;
    int cellSize = 8;
    bool stackInstructionsSet = false;
    bool iomemInstructionsSet = false;

    for (int i = 0; i < argc; i++) args.push_back(string(argv[i]));
    if (contents(args, "-h") || argc == 1 || contents(args, "--help"))
    {
        printf(help);
        return 0;
    }
    if (contents(args, "-stack"))
    {
        stackInstructionsSet = true;
    }
    if (contents(args, "-IO"))
    {
        stackInstructionsSet = true;
        printf("Sorry, IO memory not supported yet");
        return 1;
    }
    string path = args[argc - 1];

    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
    } else {
        printf("Can not open file \"%s\" check if the path is correct\n", path.c_str());
        return 1;
    }
    if (contents(args, "-c16")) cellSize = 16;
    char* file = (char*)malloc(sizeof(char) * (filesize(path.c_str()) + 1));
    memset(file, 0, (filesize(path.c_str()) + 1));
    FILE *disk = fopen(path.c_str(), "r");
    for (int i = 0; i < filesize(path.c_str()); i++) file[i] = (char)getc(disk);
    fclose(disk);

    execute(file, cellSize, stackInstructionsSet, iomemInstructionsSet);

    return 0;
}
