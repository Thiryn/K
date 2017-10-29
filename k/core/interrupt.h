#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "PIC.h"

/*
 * Send an EOI signal to OCW2 on the PICs
 */
#define END_OF_INTERRUPT				\
  asm volatile("mov $0x20, %%al\n"			\
	       "outb %%al, %0\n"			\
	       "outb %%al, %1\n"			\
	       :					\
	       : "i"(PIC_MASTER_A), "i"(PIC_SLAVE_A)	\
	       :);

/*
 * ASM ISR handler functions
 */
void generic_isr(void);
void keyboard_isr(void);
void PIT_isr(void);

/*
 * C handlers called by ASM IRS handlers, defined in callback.c
 */
extern void generic_handler();
extern void keyboard_handler();
extern void PIT_handler();

#endif /* !INTERRUPT_H_ */
