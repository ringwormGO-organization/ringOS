#include "vfs.hpp"

int min(int a,int b)
{
    if (a > b) return b;
    return a;
}

bool VFSPathEq(const char* path,const char* path2)
{
    //precompute string lenghts
    int lenA = strlen(path);
    int lenB = strlen(path2);
    int cmp = memcmp((const void*)path, (const void*)path2, min(lenA,lenB)); //basic compare
    if(cmp == 0)
    {
        //we switch to the larger string to do the comparasion or else we will hit unwanted memory and do crazy things
        if(lenA > lenB)
            return path[lenB+1]==' ' || path[lenB+1]==0; //a

        return path2[lenA+1]==' ' || path2[lenA+1]==0; //b
    }
    return false;
}

void VFSAdd(FileDescriptor toAdd)
{
    for(int i = 0; i < VFS_MAX_DESCRIPTORS; i++)
    {
        if(VFSDescriptors[i]->path[0] == 0) //free descriptor
        {
            VFSTotalEntries++;
            memcpy((void*)VFSDescriptors[i]->path+1, (void*)toAdd.path,367);
            VFSDescriptors[i]->path[0] = '/';
            VFSDescriptors[i]->source = toAdd.source;
            return;
        }
    }
}

void VFSRemove(const char* path)
{
    for(int i = 0; i < VFS_MAX_DESCRIPTORS; i++)
    {
        if(VFSPathEq(VFSDescriptors[i]->path,path))
        {
            VFSTotalEntries--;
            memset((void*)VFSDescriptors[i]->path, 0, 368);
            switch (VFSDescriptors[i]->source)
            {
                case VFS_SOURCE_RAMFS:
                    //can't remove file from ramfs
                    break;

                default:
                    //call driver to delete file from the filesystem
                    break;
                }

            return;
        }
    }
}

void VFSInit()
{
    VFSDescriptors = (FileDescriptor**)malloc(sizeof(FileDescriptor*)*VFS_MAX_DESCRIPTORS);
    for(int i = 0; i<VFS_MAX_DESCRIPTORS; i++)
    {
        VFSDescriptors[i] = (FileDescriptor*)malloc(sizeof(FileDescriptor));
        memset((void*)VFSDescriptors[i],0,sizeof(FileDescriptor));
    }
}

FileDescriptor* VFSOpenFile(const char* path)
{
    for(int i = 0; i<VFS_MAX_DESCRIPTORS; i++)
    {
        if(VFSPathEq(VFSDescriptors[i]->path,path))
            return VFSDescriptors[i];
    }
    return NULL;
}

void* VFSReadFile(FileDescriptor* file)
{
    if(file == NULL) return NULL;
    switch (file->source)
    {
        case VFS_SOURCE_RAMFS:
            return LLFSVFSHelperReader(file->path);
            break;

        default:
            return NULL; //TODO: call driver
            break;
    }
}

uint64_t VFSSizeFile(FileDescriptor* file)
{
    if(file == NULL) return 0;
    switch (file->source)
    {
        case VFS_SOURCE_RAMFS:
            return LLFSOpenFile(file->path+1)->FileSize;
            break;

        default:
            return 0; //TODO: call driver
            break;
    }
}

bool VFSExistsFileAt(const char* path)
{
    for(int i = 0; i<VFS_MAX_DESCRIPTORS; i++)
    {
        if(VFSPathEq(VFSDescriptors[i]->path,path))
            return true;
    }
    return false;
}