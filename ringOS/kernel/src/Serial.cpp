#include "Serial.hpp"

int SerialisReceived()
{
    return inportb(COM1 + 5) & 1;
}

char SerialRead()
{
    if(SerialisReceived())
        return inportb(COM1);
    else
        return 0;
}

void SerialWrite(char chr)
{
#ifdef Serial_Console
    outportb(COM1, chr);
#endif
}

void SerialWrite(const char* chr)
{
#ifdef Serial_Console
    for(int i = 0; chr[i] != '\0'; i++)
    {
        SerialWrite(chr[i]);
        if(chr[i] == '\n') SerialWrite('\r');
    }
#endif
}

void SerialClearMonitor()
{
    SerialWrite(27);
    SerialWrite("[2J");
    SerialWrite(27);
    SerialWrite("[H");
}

void SerialWrite(const char* chr,const char* chr2)
{
    SerialWrite(chr);
    SerialWrite(chr2);
}

void SerialWrite(const char* chr,const char* chr2,const char* chr3)
{
    SerialWrite(chr);
    SerialWrite(chr2);
    SerialWrite(chr3);
}

void SerialWrite(const char* chr,const char* chr2,const char* chr3,const char* chr4)
{
    SerialWrite(chr);
    SerialWrite(chr2);
    SerialWrite(chr3);
    SerialWrite(chr4);
}

void SerialWrite(const char* chr,const char* chr2,const char* chr3,const char* chr4,const char* chr5)
{
    SerialWrite(chr);
    SerialWrite(chr2);
    SerialWrite(chr3);
    SerialWrite(chr4);
    SerialWrite(chr5);
}