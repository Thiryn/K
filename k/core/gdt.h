#ifndef GDT_H_
#define GDT_H_

#include <k/types.h>

/*
 * GDT entry indexes
 */
#define KERNEL_CODE 1
#define KERNEL_DATA 2
#define USER_CODE 3
#define USER_DATA 4

/*
 * Entry type code or data
 */
#define CODE_ENTRY 1
#define DATA_ENTRY 0

/*
 * See GDT structures information at
 * https://k.lse.epita.fr/internals/protected_mode.html
 */

/*
 * GDT entry structure
 */
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


/*
 * Segment selector structure
 */
typedef struct {
  u16 rpl : 2;
  u16 ti : 1;
  u16 index : 13;
} __attribute__((packed)) seg_selector;

/*
 * GDT loader structure
 */
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdt_r;

void init_gdt(void);

#endif /* !GDT_H_ */
