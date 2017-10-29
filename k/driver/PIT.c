#include "PIT.h"
#include "k/io.h"

void init_pit(void)
{
  // PIT register configuration
  outb(PIT_CMD, PIT_CONF);

  // Set the PIT frequency
  u16 count = PIT_INTERNAL_FREQ / DESIRED_FREQ;
  outb(PIT_CR0, count & 0xff);
  outb(PIT_CR0, (count >> 8) & 0xff);
}
