#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *util_malloc(align_t align) {
  return malloc(align);
}
void *util_malloc_array(index_t count, align_t align) {
  return malloc(count * align);
}
void util_free(void *ptr) {
  free(ptr);
}
void util_swap_impl(size_t size, void *lhs, void *rhs, void *buf) {
  memcpy(buf, lhs, size);
  memcpy(lhs, rhs, size);
  memcpy(rhs, buf, size);
}
void util_memcpy(void *dst, const void *src, index_t count, align_t align) {
  assert(dst);
  if (src && 0 < count) {
    memcpy(dst, src, count * align);
  }
}
int util_strcmp(const char *lhs, const char *rhs) {
  return strcmp(lhs ? lhs : "", rhs ? rhs : "");
}
bool_t util_streq(const char *lhs, const char *rhs) {
  return lhs && rhs && strcmp(lhs, rhs) == 0;
}
const char *util_strdup(const char *src) {
  index_t count = strlen(src);
  char *dst = util_malloc_array(count + 1, 1);
  util_memcpy(dst, src, count + 1, 1);
  return dst;
}
int util_atoi(const char *str) {
  return atoi(str);
}
void util_print(const char *format, ...) {
  FILE *fp = stdout;
  va_list args;
  va_start(args, format);
  vfprintf(fp, format, args);
  va_end(args);
  fprintf(fp, "\n");
}
void util_error(const char *format, ...) {
  FILE *fp = stderr;
  va_list args;
  va_start(args, format);
  vfprintf(fp, format, args);
  va_end(args);
  fprintf(fp, "\n");
}
