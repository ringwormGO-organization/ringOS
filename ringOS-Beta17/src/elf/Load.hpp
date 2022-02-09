#pragma once

#include <stddef.h>

#include "ELF.hpp"
#include "../filesystem/llfs.hpp"
#include "../filesystem/vfs.hpp"
#include "../library/stdio.hpp"
#include "../paging/PageTableManager.hpp"
#include "../memory/heap.hpp"

void* LoadELFExecutable(const char* file, bool pie);
int CheckELF(Elf64_Ehdr* header);