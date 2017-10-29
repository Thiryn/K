#include "PIC.h"
#include "k/io.h"

void init_pic(void)
{
  // Send ICW1 to port A of each PIC
  outb(PIC_MASTER_A, ICW1);
  outb(PIC_SLAVE_A, ICW1);

  // Send ICW2 to port B of each PIC
  outb(PIC_MASTER_B, ICW2_MASTER);
  outb(PIC_SLAVE_B, ICW2_SLAVE);

  // Send ICW3 to port B of each PIC
  outb(PIC_MASTER_B, ICW3_MASTER);
  outb(PIC_SLAVE_B, ICW3_SLAVE);

  // Send ICW4 to port B of each PIC
  outb(PIC_MASTER_B, ICW4);
  outb(PIC_SLAVE_B, ICW4);

  // send OCW1 to port B of each PIC
  outb(PIC_MASTER_B, OCW1_MASTER);
  outb(PIC_SLAVE_B, OCW1_SLAVE);
}

