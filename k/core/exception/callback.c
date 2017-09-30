#include <stdio.h>

void exception_callback(void)
{
  puts("I am an exception");

  for (;;)
    continue;
}


