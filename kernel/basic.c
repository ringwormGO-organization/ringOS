#include "basic.h"

void my_reverse(char str[], int len)
{
    int start, end;
    char temp;
    for(start=0, end=len-1; start < end; start++, end--) {
        temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
    }
}

//edited implementation of itoa https://www.techcrashcourse.com/2016/02/c-program-to-implement-your-own-itoa-function.html
void itoa(unsigned long long int num, char* str, int base)
{
    int i = 0;
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }
    /* Append negative sign for negative numbers */
    str[i] = '\0';
    my_reverse(str, i);
}