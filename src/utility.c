#include "utility.h"

#include <string.h>

Bool utility_str_eq(const char *lhs, const char *rhs) {
  return lhs && rhs && 0 == strcmp(lhs, rhs);
}
int utility_str_cmp(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs);
}
void utility_memcpy(void *dst, const void *src, size_t count) {
  memcpy(dst, src, count);
}
