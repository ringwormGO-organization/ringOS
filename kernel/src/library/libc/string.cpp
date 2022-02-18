#include "string.hpp"
#include "../../memory/heap.hpp"

char str2[2];
char *char2str(char c)
{
    str2[0] = c;
    return str2;
}

int string2int(const char* str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return res;
}