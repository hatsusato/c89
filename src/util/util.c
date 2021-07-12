#include "util.h"

#include <string.h>

void util_swap_impl(size_t size, void *lhs, void *rhs, void *buf) {
  memcpy(buf, lhs, size);
  memcpy(lhs, rhs, size);
  memcpy(rhs, buf, size);
}
bool_t util_streq(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs) == 0;
}
