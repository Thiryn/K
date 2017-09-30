#include <string.h>
#include "../write.h"

int write(const char *s, size_t nb);

int puts(const char *s)
{
  int i = write(s, strlen(s));
  write("\n", 1);
  return i + 1;
}
