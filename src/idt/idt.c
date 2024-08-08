#include "idt.h"
#include "config.h"
#include "kernel.h"
#include "memory.h"

/**
 * @brief Array of IDT descriptors.
 *
 * This array contains the descriptors for all the interrupts. The size of the
 * array is defined by the LW_OS_TOTAL_INTRRUPTS macro in the config.h file.
 */
struct idt_desc idt_descriptors[LW_OS_TOTAL_INTRRUPTS];

/**
 * @brief IDT descriptor pointer.
 *
 * This struct contains the base address and the size of the IDT. It is used to
 * load the IDT into the processor.
 */
struct idtr_desc idtr_descriptors;

extern void idt_load(struct idtr_desc* ptr);

void idt_zero()
{
    print("Divide by zero error\n");
}

void idt_set(int interrupt_no, void *address) 
{
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;

}
void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptors.limit = sizeof(struct idt_desc) - 1;
    idtr_descriptors.base = (uint32_t)idt_descriptors;

    idt_set(0, idt_zero);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptors);

}