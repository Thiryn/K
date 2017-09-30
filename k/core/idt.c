#include <stdio.h>
#include "idt.h"
#include "exception/exception.h"

static struct idt_interrupt_gate_s idt_entries[IDT_SIZE];

void set_idt_handler(struct idt_interrupt_gate_s* idt, u32 handler)
{  
    idt->offset0_15 = handler & 0xffff;
    idt->dpl = 0;
    idt->present = 1;
    idt->offset16_31 = (handler >> 16) & 0xffff;
}

void load_idt()
{
  union seg_u kernel_code_selector = { .str = { 0, 0, KERNEL_CODE } };

  for (int i = 0; i < IDT_SIZE; i++) 
    {
      struct idt_interrupt_gate_s* idt = idt_entries + i; // <==> + i * sizeof(idt)
      idt->segment_selector = 0x8;//kernel_code_selector.seg;
      idt->type = INTERRUPT_GATE;
      idt->op_size = 1;
      idt->flags = 0;
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
