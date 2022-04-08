#pragma once

#include <stdint.h>
#include <stddef.h>

#include <cstdint>
#include <cstddef>
#include <limits.h>

unsigned constexpr hash(char const *input)
{
    return *input ? static_cast<unsigned int>(*input) + 33 * hash(input + 1) : 5381;
}


size_t strlen(const char *str);

char *strcpy(char *destination, const char *source);
char *strncpy(char *destination, const char *source, size_t n);

char *strcat(char *destination, const char *source);
char *strchr(const char *str, char ch);

int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);

char *strrm(char *str, const char *substr);
char *strdup(const char *src);

long strtol(const char *nPtr, char **endPtr, int base);
long long int strtoll(const char *nPtr, char **endPtr, int base);
unsigned long strtoul(const char *nPtr, char **endPtr, int base);
unsigned long long int strtoull(const char *nPtr, char **endPtr, int base);

char** strsplit(const char* s, const char* delim);
char** strsplit_count(const char* s, const char* delim, size_t &nb);

char *strstr(const char *str, const char *substr);
int lstrstr(const char *str, const char *substr, int skip = 0);

char *getline(const char *str, const char *substr, char *buffer, int skip = 0);

char *reverse(char *str);

bool isspace(char c);
bool isempty(char *str);
static inline bool isempty(const char *str)
{
    return isempty(const_cast<char*>(str));
}

int isdigit(int c);
int isalpha(int c);
int islower(int c);

char tolower(char c);
char toupper(char c);
int tonum(char c);
char *tostr(char c);

char *int2string(int num);
int string2int(const char *str);

char *char2str(char c);