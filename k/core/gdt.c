#include "gdt.h"
#include <stdio.h>

// Macro to set the value of an entry in the GDT table
#define ADD_GDT_ENTRY(base, limit, t, privileges)		\
  {								\
    .limit0 = limit & 0xffff,					\
    .base0 = base & 0xffffff,					\
    .type = ((t == CODE_ENTRY) ? 15 : 7),			\
    .d_type = 1,						\
    .dpl = privileges & 0b11,					\
    .present = 1,						\
    .limit1 = (limit >> 16) & 0xf,				\
    .avl = 0,							\
    .l = 0,							\
    .dsize = 1,							\
    .granul = 1,						\
    .base1 = (base >> 24) & 0xff				\
  }

/*
 * The GDT table
 * First entry always NULL
 */
gdt_entry   gdt_entries[3] = {
  {0,}, // NULL SEGMENT
  ADD_GDT_ENTRY(0, 0xfffff, CODE_ENTRY, 0), // Kernel Code Segment
  ADD_GDT_ENTRY(0, 0xfffff, DATA_ENTRY, 0), // Kernel Data Segment
  /* ADD_GDT_ENTRY(0, 0xfffff, CODE_ENTRY, 3), // User Code Segment */
  /* ADD_GDT_ENTRY(0, 0xfffff, DATA_ENTRY, 3), // User Data Segment */
};

/*
 * Get the CR0 value in a register,
 * Set the PE (protection enabled) bit (first one) in the register
 * And put eax back into cr0
 */
static void enter_protected_mode()
{
  asm volatile("movl %cr0, %eax\n"
	       "orl 0x1, %eax\n"
	       "movl %eax, %cr0\n");
}

/*
 * Set the data segment selector in the segment register (ds, ss, es, fs, gs)
 * Then, set the code segment, but "jump" to a fake label "1", continuing our code
 */
static void load_segments (void) {
  seg_selector data = { 0, 0, KERNEL_DATA };
  seg_selector code = { 0, 0, KERNEL_CODE };
  
  asm volatile ("movw %0, %%ax \n"
		"movw %%ax, %%ds \n"
		"movw %%ax, %%ss \n"
		"movw %%ax, %%es \n"
		"movw %%ax, %%fs \n"
		"movw %%ax, %%gs \n"
		:
		: "d" (data)
		: "ax");
  
  asm volatile (
		"pushl %0\n"
		"pushl $1f \n"
		"lret\n"
		"1:"
		:
		: "d" (code)
		:
		);
}

/*
 * Helper function to debug a gdt entry
 */
/* static void print_gdt(gdt_entry *e) */
/* { */
/*   printf("GDT ENTRY\n" */
/* 	 "limit0\t0x%X\n" */
/* 	 "base0\t0x%X\n" */
/* 	 "type\t0x%X\n" */
/* 	 "descriptor type\t0x%X\n" */
/* 	 "privileges (DPL)\t0x%X\n" */
/* 	 "present\t0x%X\n" */
/* 	 "limit1\t0x%X\n" */
/* 	 "avl\t0x%X\n" */
/* 	 "l\t0x%X\n" */
/* 	 "d/b op size\t0x%X\n" */
/* 	 "granularity\t0x%X\n" */
/* 	 "base1\t0x%X\n\n", */
/* 	 e->limit0, e->base0, e->type, e->d_type, e->dpl, e->present, e->limit1, */
/* 	 e->avl, e->l, e->dsize, e->granul, e->base1); */
/* } */

/*
 * Init the GDT array, load it with 'lgdt', enter protected mode and load the segments
 *
 */
void init_gdt(void)
{
  enter_protected_mode();
  // Load GDT
  gdt_r gdtr;
  
  gdtr.base = (u32)gdt_entries; /* gdt base address */
  gdtr.limit = sizeof(gdt_entries) - 1; /* gdt size - 1 */
  asm volatile("lgdt %0\n"
	       : /* no output */
	       : "m" (gdtr)
	       : "memory");
  
  load_segments();
}
