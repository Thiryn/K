#ifndef IDT_H_
#define IDT_H_

#include <k/types.h>
#include "gdt.h"

#define IDT_SIZE 256

#define INTERRUPT_GATE  0b110

// EXCEPTIONS
#define EXCEPTION_DIVIDE_ERROR     0

void init_idt(void);

typedef struct {
  u32 offset0 : 16;
  u32 segment_selector : 16;
  u32 reserved: 5;
  u32 unused: 3;
  u32 type: 3;
  u32 op_size : 1;
  u32 zero: 1;
  u32 dpl: 2;
  u32 present: 1;
  u32 offset1 : 16;
} __attribute__((packed)) idt_interrupt_gate;

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_r;

union seg_u
{
  u16 seg;
  seg_selector str;
};

#endif /* !IDT_H_ */
