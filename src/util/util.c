#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *util_malloc(align_t align, index_t index) {
  return malloc(index * align);
}
void *util_malloc_array(align_t align, index_t count) {
  return malloc(align * count);
}
void util_free(void *ptr) {
  free(ptr);
}
void util_swap_impl(size_t size, void *lhs, void *rhs, void *buf) {
  memcpy(buf, lhs, size);
  memcpy(lhs, rhs, size);
  memcpy(rhs, buf, size);
}
int util_strcmp(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs);
}
bool_t util_streq(const char *lhs, const char *rhs) {
  return strcmp(lhs, rhs) == 0;
}
const char *util_strdup(const char *src) {
  index_t count = 1 + strlen(src);
  char *dst = util_malloc_array(1, count);
  strncpy(dst, src, count);
  return dst;
}
void util_print(const char *msg) {
  printf("%s\n", msg);
}
void util_error(const char *msg) {
  fprintf(stderr, "%s\n", msg);
}
