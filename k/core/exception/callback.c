#include <stdio.h>
#include "io.h"
#include "interrupt.h"
#include "write.h"

void generic_handler()
{
  puts("Interrupt");
  END_OF_INTERRUPT
}

void keyboard_handler()
{
  u8 c = inb(0x60);
  printf("%d", c);
  END_OF_INTERRUPT  
}

void PIT_handler()
{
  puts("PIT");
  END_OF_INTERRUPT  
}

