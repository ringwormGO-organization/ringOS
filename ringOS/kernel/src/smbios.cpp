#include "smbios.h"

using namespace GUI::Renderer;

SMBiosHeader* hdr;

void SMBiosParse(SMBiosHeader* hdr)
{
    SMBiosEntry* entry = (SMBiosEntry*)((uint64_t)hdr->TableAddress);
    printf("SMBios entries: %u\n",hdr->TableLength);
    for(int i = 0; i < hdr->TableLength; i++)
    {
        printf("%u ",entry->Type);
        entry += entry->Lenght+sizeof(SMBiosEntry);
    }
    printf("\n");
}