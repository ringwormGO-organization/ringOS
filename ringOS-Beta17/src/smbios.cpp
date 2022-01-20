#include "smbios.h"

using namespace Renderer;

SMBiosHeader* hdr;

void SMBiosParse(SMBiosHeader* hdr)
{
    SMBiosEntry* entry = (SMBiosEntry*)((uint64_t)hdr->TableAddress);
    GlobalRenderer->printf("SMBios entries: %u\n",hdr->TableLength);
    for(int i = 0; i<hdr->TableLength; i++)
    {
        GlobalRenderer->printf("%u ",entry->Type);
        entry += entry->Lenght+sizeof(SMBiosEntry);
    }
    GlobalRenderer->printf("\n");
}