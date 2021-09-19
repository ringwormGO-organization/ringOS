#include "cstr.h"

char uintTo_StringOutput[128];
const char* to_string(uint64_t value) 
{
    uint8_t size;
    uint64_t sizeTest = value;
    while(sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0) 
    {
        uint8_t remainder = value % 10;
        value /= 10;
        uintTo_StringOutput[size - index] = remainder + '0';
        index++;
    }
    uint8_t reminde = value % 10;
    uintTo_StringOutput[size - index] = reminde + '0';
    uintTo_StringOutput[size + 1] = 0;
    return uintTo_StringOutput;
}

char intTo_StringOutput[128];
const char* to_string(int64_t value)
{
    uint8_t isNegative = 0;

    if (value < 0)
    {
       isNegative = 1;
       value *= -1;
       intTo_StringOutput[0] = '-';
    }

    uint8_t size;
    uint64_t sizeTest = value;
    while(sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0) 
    {
        uint8_t remainder = value % 10;
        value /= 10;
        intTo_StringOutput[isNegative + size - index] = remainder + '0';
        index++;
    }
    uint8_t reminde = value % 10;
    intTo_StringOutput[isNegative + size - index] = reminde + '0';
    intTo_StringOutput[isNegative + size + 1] = 0;
    return intTo_StringOutput;
}