#pragma once
#include <stdint.h>

typedef struct ACPI_RSDP 
{
    uint8_t signature[8];
    uint8_t checksum;
    uint8_t OEMid[6];
    uint8_t revision;
    uint32_t RSDT_address;
    uint32_t lenght;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
}ACPI_RSDP;

typedef struct ACPI_SDTHeader
{
    uint8_t Signature[4];
    uint32_t len;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t oem_tableid[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
}ACPI_SDTHeader;

typedef struct MCFGHeader
{
    ACPI_SDTHeader header;
    uint64_t reserved;


}MCFGHeader;

typedef struct DevConfig 
{
    uint64_t BaseAddress;
    uint16_t PCISegGroup;
    uint8_t start_bus;
    uint8_t end_bus;
    uint32_t reserved;
}DevConfig;

void* ACPI_FindTable(ACPI_SDTHeader* sdtheader,char* signature);