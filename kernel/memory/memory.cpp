#include "memory.hpp"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize)
{
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) return memorySizeBytes;

    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;

}

void memset(void* start, uint8_t value, uint64_t num){
    for (uint64_t i = 0; i < num; i++){
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}

void memcpy(void *d, const void *s, size_t n)
{
    uint64_t d0, d1, d2;
    __asm__ volatile(
        "rep ; movsq\n\t""movq %4,%%rcx\n\t""rep ; movsb\n\t": "=&c" (d0),
        "=&D" (d1),
        "=&S" (d2): "0" (n >> 3),
        "g" (n & 7),
        "1" (d),
        "2" (s): "memory"
    );  //not mine (found it on reddit: https://www.reddit.com/r/C_Programming/comments/ivoqhk/understanding_the_assembly_code_of_memcpy/)
}

int memcmp(const void *aptr, const void *bptr, size_t n)
{
    const unsigned char *a = (const unsigned char*)aptr, *b = (const unsigned char*)bptr;
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] < b[i])
            return -1;
        else if (a[i] > b[i])
            return 1;
    }
    return 0;
}
