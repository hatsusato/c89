#include "utility.h"

#include <stdlib.h>
#include <string.h>

void *utility_malloc(size_t size) {
  return malloc(size);
}
void utility_free(void *var) {
  free(var);
}
void utility_memcpy(void *dst, const void *src, size_t count) {
  memcpy(dst, src, count);
}
int utility_memcmp(const void *lhs, const void *rhs, size_t count) {
  return memcmp(lhs, rhs, count);
}
