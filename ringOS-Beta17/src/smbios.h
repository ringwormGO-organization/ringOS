#pragma once

#include <stdint.h>

#include "BasicRenderer.hpp"

struct SMBiosHeader
{
    char Signature[4];
    uint8_t Checksum;
    uint8_t Length;
    uint8_t MajorVersion;
    uint8_t MinorVersion;
    uint16_t MaxStructureSize;
    uint8_t EntryPointRevision;
    char FormattedArea[5];
    char Signature2[5];
    uint8_t Checksum2;
    uint16_t TableLength;
    unsigned int TableAddress;
    uint16_t NumberOfStructures;
    uint8_t BCDRevision;
};

struct SMBiosEntry
{
    uint8_t Type;
    uint8_t Lenght;
    uint16_t Handle;
};

struct SMBiosType0
{
    uint8_t Type;
    uint8_t Lenght;
    uint16_t Handle;
    uint8_t Vendor;
    uint8_t BIOSVersion;
    uint16_t BIOSStartingAddressSegment;
    uint8_t BIOSReleaseDate;
    uint8_t BIOSROMSize;
    uint32_t BIOSCharacteristics;
};

void SMBiosParse();