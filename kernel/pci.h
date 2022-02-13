#pragma once
#include <stdint.h>
#include <stddef.h>

#include "acpi.h"

typedef struct DeviceHeader 
{
uint16_t VendorID;
uint16_t DeviceID;
uint16_t Command;
uint16_t Status;
uint8_t RevisionID;
uint8_t ProgIf;
uint8_t Subclass;
uint8_t Class;
uint8_t CacheLineSize;
uint8_t LatencyTimer;
uint8_t HeaderType;
uint8_t BIST;

}DeviceHeader;

void EnumeratePCI(MCFGHeader* mfghdr);