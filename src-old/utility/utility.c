#include "utility/utility.h"

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
void utility_memmove(void *dst, const void *src, size_t count) {
  memmove(dst, src, count);
}
int utility_memcmp(const void *lhs, const void *rhs, size_t count) {
  return memcmp(lhs, rhs, count);
}
int utility_strcmp(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs);
}
int utility_intcmp(int lhs, int rhs) {
  return (lhs < rhs) ? -1 : (lhs > rhs);
}
int utility_ptrcmp(const void *lhs, const void *rhs) {
  return (lhs < rhs) ? -1 : (lhs > rhs);
}
