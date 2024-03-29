#include <stdio.h>
#include "k/io.h"
#include "interrupt.h"
#include "k/write.h"
#include "PIT.h"

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
  pit_increment_tick();
  END_OF_INTERRUPT
}

