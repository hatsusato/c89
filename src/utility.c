#include "utility.h"

#include <stdlib.h>
#include <string.h>

Bool utility_str_eq(const char *lhs, const char *rhs) {
  return lhs && rhs && 0 == strcmp(lhs, rhs);
}
void *utility_malloc(size_t size) {
  return malloc(size);
}
void utility_free(void *ptr) {
  free(ptr);
}
void utility_memcpy(void *dst, const void *src, size_t count) {
  memcpy(dst, src, count);
}
