#pragma once

/* Mainly used for customizing printed text. Comment to disable a setting, uncomment to enable */

/* kernelUtil.cpp */
//#define RESET_SCREEN

/* kernel.cpp */
#define ENABLE_PRINTED_TEXT
#define RESOLUTION
//#define RAM_INFO
//#define RSDP_CHECK
#define SMBIOS_INFO
//#define MALLOC_EXAMPLE
//#define PAGE_FAULT

/* panic.cpp */
#define PANIC_COLOR 0xff00ffff

#define PRINT_RAM_INFO

//#define SHUTDOWN
//#define REBOOT