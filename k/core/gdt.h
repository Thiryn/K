#ifndef GDT_H_
#define GDT_H_

#include <k/types.h>

#define KERNEL_CODE 1
#define KERNEL_DATA 2

#define CODE_ENTRY 1
#define DATA_ENTRY 0

#define GDT_INDICATOR 0x0
#define LDT_INDICATOR 0x1

typedef struct
{
  u64	limit0	: 16;
  u64	base0	: 24;
  u64	type	: 4;
  u64	d_type	: 1;
  u64	dpl	: 2;
  u64	present	: 1;
  u64	limit1	: 4;
  u64	avl	: 1;
  u64	l	: 1;
  u64	dsize	: 1;
  u64	granul	: 1;
  u64	base1	: 8;  
} __attribute__((packed)) gdt_entry;

typedef struct {
  u16 rpl : 2;
  u16 ti : 1;
  u16 index : 13;
} __attribute__((packed)) seg_selector;

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdt_r;

void init_gdt(void);

#endif /* !GDT_H_ */
