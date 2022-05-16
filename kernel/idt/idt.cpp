#include <stdbool.h>

#include "idt.hpp"

static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS];

extern "C" void* isr_stub_table[500];
 
__attribute__((aligned(0x10))) 
static idt_desc_t idt[256]; // Create an array of IDT entries; aligned for performance

extern "C" __attribute__((noreturn)) void exception_handler() {
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_desc_t* descriptor = &idt[vector];
 
    descriptor->base_low       = (uint64_t)isr & 0xFFFF;
    descriptor->cs             = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->base_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->base_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->rsv0           = 0;
}

void idt_init() {

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_desc_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}
