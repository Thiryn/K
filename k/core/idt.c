#include <stdio.h>
#include "idt.h"
#include "exception/exception.h"

static idt_interrupt_gate idt_entries[IDT_SIZE];

/*
 * Set a handler for an interrupt index
 */
void set_idt_handler(idt_interrupt_gate* idt, u32 handler)
{  
    idt->offset0 = handler & 0xffff;
    idt->dpl = 0;
    idt->present = 1;
    idt->offset1 = (handler >> 16) & 0xffff;
}

/*
 * Load the IDT table
 * The first 32 entries are for exceptions
 */
void init_idt(void)
{
  union seg_u kernel_code_selector = { .str = { 0, 0, KERNEL_CODE } };

  for (int i = 0; i < IDT_SIZE; i++) 
    {
      idt_interrupt_gate* idt = idt_entries + i; // <==> + i * sizeof(idt)
      idt->segment_selector = kernel_code_selector.seg;
      idt->type = INTERRUPT_GATE;
      idt->op_size = 1;
      idt->unused = 0;
      idt->zero = 0;
      set_idt_handler(idt, (u32)exception_handler);
      idt->present = (i < 32) ? 1 : 0;
    }

  idt_r idtr;
  idtr.base = (u32)idt_entries;
  idtr.limit = sizeof(idt_entries) - 1;
  asm volatile (
		"lidt %0\n"
		:
		: "m" (idtr)
		: "memory"
		);
}
