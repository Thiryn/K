#include <limits.h>
#include <assert.h>
#include "k/ring.h"

void ring_test(u16 size)
{
  {
    RING_CREATE(u16, test_ring, size);
    assert(RING_GET(test_ring) == -1);

    for (u16 i = 0; i <= size; ++i)
      RING_ADD(test_ring, i);
    for (u16 i = size; i > 0; --i)
      assert(RING_GET(test_ring) == i);
    assert(RING_GET(test_ring) == -1);
  }
}

void ring_test_main()
{
  ring_test(0);
  ring_test(1);
  ring_test(5);
  ring_test(100);
  ring_test(512);
  ring_test(USHRT_MAX - 1);
}
