#include "util.h"

#include <stdlib.h>
#include <string.h>

void *util_malloc(align_t align, index_t index) {
  return malloc(index * align);
}
void util_free(const void *ptr) {
  free((void *)ptr);
}
void util_swap_impl(size_t size, void *lhs, void *rhs, void *buf) {
  memcpy(buf, lhs, size);
  memcpy(lhs, rhs, size);
  memcpy(rhs, buf, size);
}
bool_t util_streq(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs) == 0;
}
