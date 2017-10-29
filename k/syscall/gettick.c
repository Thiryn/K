#include "PIT.h"

unsigned long gettick(void)
{
  return pit_get_tick();
}
