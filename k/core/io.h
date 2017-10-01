#ifndef IO_H_
#define IO_H_

#include <k/types.h>

static inline void outb(u16 port, u8 val)
{
  asm volatile ("outb %0, %1\n\t"
		:
		: "a"(val), "d"(port));
}
 
static inline u8 inb(u16 port)
{
  u8 ret;
  asm volatile ("inb %1, %0\n\t"
		: "=&a" (ret)
		: "d" (port));
  return ret;
}

#endif				/* !IO_H_ */
