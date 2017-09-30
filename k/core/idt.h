#ifndef IDT_H_
#define IDT_H_

#include <k/types.h>
#include "gdt.h"

#define IDT_SIZE 256

#define INTERRUPT_GATE  0b110

// EXCEPTIONS
#define EXCEPTION_DIVIDE_ERROR     0

void load_idt();

/* typedef struct { */
/*   u32 offset0 : 16; */
/*   u32 segment_selector : 16; */
/*   u32 reserved: 5; */
/*   u32 unused: 3; */
/*   u32 type: 3; */
/*   u32 op_size : 1; */
/*   u32 zero: 1; */
/*   u32 dpl: 2; */
/*   u32 present: 1; */
/*   u32 offset1 : 16; */
/* } __attribute__((packed)) idt_interrupt_gate; */

typedef struct idt_interrupt_gate_s {
  u16 offset0_15;
  u16 segment_selector;
  u8 reserved: 5;
  u8 flags: 3;
  u8 type: 3;
  u8 op_size: 1;
  u8 zero: 1;
  u8 dpl: 2;
  u8 present: 1;
  u16 offset16_31;
} __attribute__((packed)) idt_interrupt_gate_t;

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
