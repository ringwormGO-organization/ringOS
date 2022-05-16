#include <stdint.h>

#include "../gdt/gdt.hpp"

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t	base_low;
	uint16_t	cs;
	uint8_t	    ist;
	uint8_t     attributes;
	uint16_t    base_mid;
	uint32_t    base_high;
	uint32_t    rsv0;
} __attribute__((packed)) idt_desc_t;

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

void idt_init();
