#pragma once

#include <stdint.h>

void blank();
void fill();
void put();

// This should go outside any function..
extern "C" void loadPageDirectory(unsigned int*);
extern "C" void enablePaging();