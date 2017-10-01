#include "PIC.h"
#include "k/io.h"

void init_pic(void)
{
  outb(PIC_MASTER_A, ICW1);
  outb(PIC_SLAVE_A, ICW1);

  outb(PIC_MASTER_B, ICW2_MASTER);
  outb(PIC_SLAVE_B, ICW2_SLAVE);

  outb(PIC_MASTER_B, ICW3_MASTER);
  outb(PIC_SLAVE_B, ICW3_SLAVE);

  outb(PIC_MASTER_B, ICW4);
  outb(PIC_SLAVE_B, ICW4);

  outb(PIC_MASTER_B, OCW1_MASTER);
  outb(PIC_SLAVE_B, OCW1_SLAVE);
}

void init_pit(void)
{
  // PIT register configuration
  outb(PIT_CMD, PIT_CONF);
  u16 count = PIT_INTERNAL_FREQ / DESIRED_FREQ;
  outb(PIT_CR0, count & 0xff);
  outb(PIT_CR0, (count >> 8) & 0xff);
}
