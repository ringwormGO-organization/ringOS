#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../paging/PageFrameAllocator.hpp"
#include "llfs.hpp"
#include "../memory/heap.hpp"

#define VFS_SOURCE_RAMFS 1

#define VFS_MAX_DESCRIPTORS 0x19F

struct FileDescriptor
{
    char path[368] = {0};
    uint8_t source = 0;
};

inline uint8_t VFSSource = 0;
inline uint64_t VFSTotalEntries = 0;
inline FileDescriptor** VFSDescriptors;

bool VFSPathEq(const char* path,const char* path2);

bool VFSExistsFileAt(const char* path);
FileDescriptor* VFSOpenFile(const char* path);
void* VFSReadFile(FileDescriptor* file);
uint64_t VFSSizeFile(FileDescriptor* file);
void VFSInit();
void VFSAdd(FileDescriptor toAdd);
void VFSRemove(const char* path);