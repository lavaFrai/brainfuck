#pragma once
#include <cstdio>
#include <stack>

using namespace std;


int execute(const char *file, int cellSize=8, bool stackInstructionsSet=false, bool iomemInstructionsSet=false)
{
    long long programPtr = 0;
    long long dataPtr = 0;
    uint8_t *ram = (uint8_t*) malloc(256);
    memset(ram, 0, 256);

    stack<uint8_t> _stack;

    while (file[programPtr] != 0)
    {
        if (file[programPtr] == '>') dataPtr++;
        else if (file[programPtr] == '<') dataPtr--;
        else if (file[programPtr] == '+') ram[dataPtr]++;
        else if (file[programPtr] == '-') ram[dataPtr]--;
        else if (file[programPtr] == '.') putchar(ram[dataPtr]);
        else if (file[programPtr] == ',') ram[dataPtr] = getchar();
        else if (file[programPtr] == '[') {
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
        }
        else if (file[programPtr] == ']') {
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
        }
        else if ((file[programPtr] >= 'a' && file[programPtr] <= 'z') ||
                (file[programPtr] >= 'A' && file[programPtr] <= 'Z') ||
                (file[programPtr] >= '0' && file[programPtr] <= '9'))
            {
                ram[dataPtr] = file[programPtr];
            }

        else if (stackInstructionsSet && file[programPtr] == '#') _stack.push(ram[dataPtr]);
        else if (stackInstructionsSet && file[programPtr] == '$')
        {
            ram[dataPtr] = _stack.top();
            _stack.pop();
        }
        else {
            // Invalid instruction interruption

        }

        programPtr++;
    }
    return 0;
}
