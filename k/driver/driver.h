#ifndef DRIVER_H_
#define DRIVER_H_

#include "k/serial.h"

void init_driver(void)
{
  init_serial(COM1);
}

#endif /* !DRIVER_H_*/
