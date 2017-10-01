.extern generic_handler
.extern keyboard_handler
.extern PIT_handler
	
.global generic_isr
.global keyboard_isr
.global PIT_isr
	
.macro SAVE_REG 
  pusha
  pushw %ds
  pushw %es
  pushw %fs
  pushw %gs
  pushl %ebx
  mov $0x10, %bx
  mov %bx, %ds
  popl %ebx
.endm

.macro RESTORE_REG 
  popw %gs
  popw %fs
  popw %es
  popw %ds
  popa
.endm
	
generic_isr:
	pusha
	call generic_handler
	popa
	iret

keyboard_isr:
	SAVE_REG
	call keyboard_handler
	RESTORE_REG
	iret

PIT_isr:
	SAVE_REG
	call PIT_handler
	RESTORE_REG
	iret
