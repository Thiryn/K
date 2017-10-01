#include "k/ring.h"

RING_CREATE_STATIC(u8, pressed_keys, 255);

void addkey(u8 scancode)
{
  bool pressed = (scancode & 0b10000000) != 0 ? true : false;

  if (pressed == false)
    return;

  u8 keynum =  scancode & 0b01111111;
  RING_ADD(pressed_keys, keynum);
}

int getkey(void)
{
  return RING_GET(pressed_keys);
}
