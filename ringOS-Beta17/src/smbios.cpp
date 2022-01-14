#include "smbios.h"

SMBiosHeader* hdr;

void SMBiosParse()
{
    SMBiosEntry* entry = (SMBiosEntry*)((uint64_t)hdr->TableAddress);
    GlobalRenderer->Print("SMBIOS entries: ");
    GlobalRenderer->Print(to_hstring((uint16_t)hdr->TableLength));
    for(int i = 0; i<hdr->TableLength; i++)
    {
        GlobalRenderer->Print(to_hstring((uint8_t)entry->Type));
        entry += entry->Lenght+sizeof(SMBiosEntry);
    }
    GlobalRenderer->Print("\n");
}