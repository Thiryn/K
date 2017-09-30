#include "gdt.h"
#include <stdio.h>
#define CODE_ENTRY 1
#define DATA_ENTRY 0

#define GDT_INDICATOR 0x0
#define LDT_INDICATOR 0x1

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

static void enter_protected_mode()
{
  /* puts("BDG Enter Protected Mode"); */
  /* puts("BDG Set PE flag in CR0"); */
  asm volatile("movl %cr0, %eax\n"
	       "orl 0x1, %eax\n"
	       "movl %eax, %cr0\n");
}

static void load_segments () {
  seg_selector data = { 0, 0, KERNEL_DATA };
  seg_selector code = { 0, 0, KERNEL_CODE };

  /* printf("DBG load segments\n" */
  /* 	 "DBG set ds, ss, es, fs, gs to data segment 0x%X", data); */
  
  asm volatile ("movw %0, %%ax \n\
    movw %%ax, %%ds \n		 \
    movw %%ax, %%ss \n		 \
    movw %%ax, %%es \n		 \
    movw %%ax, %%fs \n		 \
    movw %%ax, %%gs \n"
		:
		: "d" (data)
		: "ax");
  
  /* printf("DBG pushl to code segent 0x%X, and go to label 1", code); */
  asm volatile (
   "pushl %0\n	 \
    pushl $1f \n		 \
    lret\n \
    1:"
		:
		: "d" (code)
		:
		);
  /* puts("DBG segment loaded"); */
}

void print_gdt(gdt_entry *e)
{
  printf("GDT ENTRY\n"
	 "limit0\t0x%X\n"
	 "base0\t0x%X\n"
	 "type\t0x%X\n"
	 "descriptor type\t0x%X\n"
	 "privileges (DPL)\t0x%X\n"
	 "present\t0x%X\n"
	 "limit1\t0x%X\n"
	 "avl\t0x%X\n"
	 "l\t0x%X\n"
	 "d/b op size\t0x%X\n"
	 "granularity\t0x%X\n"
	 "base1\t0x%X\n\n",
	 e->limit0, e->base0, e->type, e->d_type, e->dpl, e->present, e->limit1, e->avl, e->l, e->dsize, e->granul, e->base1);
}
  gdt_entry   gdt_entries[5] = {
    {0,}, // NULL SEGMENT
    ADD_GDT_ENTRY(0, 0xfffff, CODE_ENTRY, 0), // Kernel Code Segment
    ADD_GDT_ENTRY(0, 0xfffff, DATA_ENTRY, 0), // Kernel Data Segment
    ADD_GDT_ENTRY(0, 0xfffff, CODE_ENTRY, 3), // User Data Segment
    ADD_GDT_ENTRY(0, 0xfffff, DATA_ENTRY, 3), // User Data Segment
  };

void init_segments()
{
  /* puts("DBG : creating gdt entries");  */
  // Set GDT

  /* printf("DBG sizeof sole entry : %d\n" */
  /* 	 "DBG sizeof gdt array : %d\n", sizeof(gdt_entry), sizeof(gdt_entries)); */
  /* puts("DBG NULL SEGMENT"); */
  /* print_gdt(&(gdt_entries[0])); */

  /* puts("DBG KERNEL CODE SEGMENT"); */
  /* print_gdt(&(gdt_entries[KERNEL_CODE])); */

  /* puts("DBG KERNEL DATA SEGMENT"); */
  /* print_gdt(&(gdt_entries[KERNEL_DATA])); */

  // Load GDT
  gdt_r gdtr;
  
  gdtr.base = (u32)gdt_entries; /* gdt base address */
  gdtr.limit = sizeof(gdt_entries) - 1; /* gdt size - 1 */
  /* printf("DBG gdtr.base : 0x%X\n" */
  /* 	 "DBG gdtr.limit : 0x%X\n", gdtr.base, gdtr.limit); */
  /* puts("BDG exec lgdt"); */
  asm volatile("lgdt %0\n"
	       : /* no output */
	       : "m" (gdtr)
	       : "memory");
  
  enter_protected_mode();
  load_segments();
}
