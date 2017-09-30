#include "io.h"
#include "serial.h"

int is_transmit_empty() {
   return inb(COM1 + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
   outb(COM1, a);
}

int write(const char *s, size_t nb)
{
  for (; nb > 0; --nb)
    {
      write_serial(*s);
      s++;
    }
}
