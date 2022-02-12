#pragma once

#include <stdint.h>

#include "BasicRenderer.hpp"

struct SMBiosHeader
{
    char EntryPointString[4];    //This is _SM_
 	uint8_t Checksum;              //This value summed with all the values of the table, should be 0 (overflow)
 	uint8_t Length;                //Length of the Entry Point Table. Since version 2.1 of SMBIOS, this is 0x1F
 	uint8_t MajorVersion;          //Major Version of SMBIOS
 	uint8_t MinorVersion;          //Minor Version of SMBIOS
 	uint8_t MaxStructureSize;     //Maximum size of a SMBIOS Structure (we will se later)
 	uint8_t EntryPointRevision;    //...
 	char FormattedArea[5];       //...
 	char EntryPointString2[5];   //This is _DMI_
 	uint8_t Checksum2;             //Checksum for values from EntryPointString2 to the end of table
 	uint8_t TableLength;          //Length of the Table containing all the structures
 	uint8_t TableAddress;	     //Address of the Table
 	uint8_t NumberOfStructures;   //Number of structures in the table
 	uint8_t BCDRevision;           //Unused
};

struct SMBiosEntry
{
    uint8_t Type;
    uint8_t Lenght;
    uint16_t Handle;
};

size_t SMBiosParse(SMBiosHeader* hdr);