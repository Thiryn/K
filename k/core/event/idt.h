#ifndef IDT_H_
#define IDT_H_

#include <k/types.h>
#include "gdt.h"

#define IDT_SIZE 255 /* Size of the IDT */

/*
 * Type of the IDT
 */
#define INTERRUPT_GATE  0b110
#define TRAP_GATE  0b111
#define TASK_GATE  0b101

// EXCEPTIONS
#define EXCEPTION_DIVIDE_ERROR     0

/*
 * IDT entry structure
 */
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

/*
 * IDT loader structure
 */
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_r;

/*
 * Segment selector translation
 */
union seg_u
{
  u16 seg;
  seg_selector str; // see gdt.h
};

/*
 * Function to call to initialize the IDT table
 */
void init_idt(void);

#endif /* !IDT_H_ */
