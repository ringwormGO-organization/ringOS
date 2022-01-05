#include <stdint.h>
#include "acpi.h"

void* ACPI_FindTable(ACPI_SDTHeader* sdtheader,char* signature)
{
    int entries = sdtheader->len;
    for(int t = 0;t < entries;t++)
    {
        ACPI_SDTHeader* newstd = (ACPI_SDTHeader*)*(uint64_t*)((uint64_t)sdtheader + sizeof(ACPI_SDTHeader) + (t * 8));
        for(int j = 0;j < 4;j++)
        {
            if(newstd->Signature[j] != signature[j])
            {
                break;
            }
            if (j == 3) return newstd;
        }
    }    
}