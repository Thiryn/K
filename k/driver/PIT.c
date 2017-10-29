#include "PIT.h"
#include "k/io.h"

/*
 * The counter incremented at each PIT interrupt
 */
static unsigned long tick = 0;

void init_pit(void)
{
  // PIT register configuration
  outb(PIT_CMD, PIT_CONF);

  // Set the PIT frequency
  u16 count = PIT_INTERNAL_FREQ / DESIRED_FREQ;
  outb(PIT_CR0, count & 0xff);
  outb(PIT_CR0, (count >> 8) & 0xff);
}

void pit_increment_tick(void)
{
  tick++;
}

unsigned long pit_get_tick(void)
{
  return tick;
}
