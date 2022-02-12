#pragma once

#include "IO.hpp"

#define COM1 0x3F8

void SerialWrite(char chr);
void SerialWrite(const char* chr);
void SerialWrite(const char* chr,const char* chr2);
void SerialWrite(const char* chr,const char* chr2,const char* chr3);
void SerialWrite(const char* chr,const char* chr2,const char* chr3,const char* chr4);
void SerialWrite(const char* chr,const char* chr2,const char* chr3,const char* chr4,const char* chr5);
char SerialRead();
void SerialClearMonitor();
int SerialisReceived();