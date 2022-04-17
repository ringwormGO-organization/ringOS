#include "smbios.h"

using namespace GUI::Text;

SMBiosHeader* hdr;

size_t SMBiosParse(SMBiosHeader* hdr)
{
    size_t i;
    const char *strtab = (char *)hdr + hdr->Length;
    // Scan until we find a double zero byte
    for (i = 1; strtab[i - 1] != '\0' || strtab[i] != '\0'; i++)
        ;
    return hdr->Length + i + 1;
}