#pragma once
#include <cstdio>

using namespace std;


int execute(const char *file, int cellSize=8, bool stackInstructionsSet=false, bool iomemInstructionsSet=false)
{
    long long programPtr = 0;
    long long dataPtr = 0;
    uint8_t *ram = (uint8_t*) malloc(256);
    memset(ram, 0, 256);

    while (file[programPtr] != 0)
    {
        switch (file[programPtr]) {
            case '>':
                dataPtr++;
                break;
            case '<':
                dataPtr--;
                break;
            case '+':
                ram[dataPtr]++;
                break;
            case '-':
                ram[dataPtr]--;
                break;
            case '.':
                putchar(ram[dataPtr]);
                break;
            case ',':
                ram[dataPtr] = getchar();
                break;
            case '[':
                if (ram[dataPtr] == 0)
                {
                    int scanLine = 1;
                    while (scanLine)
                    {
                        programPtr++;
                        if (file[programPtr] == '[') scanLine++;
                        if (file[programPtr] == ']') scanLine--;
                    }
                }
                break;
            case ']':
                if (ram[dataPtr] != 0)
                {
                    int scanLine = 1;
                    while (scanLine)
                    {
                        programPtr--;
                        if (file[programPtr] == '[') scanLine--;
                        if (file[programPtr] == ']') scanLine++;
                    }
                }
                break;

        }
        programPtr++;
    }
    return 0;
}
