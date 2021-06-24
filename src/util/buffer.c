#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void buffer_init(struct buffer *buf, void *ptr, size_t size) {
  buf->ptr = ptr;
  buf->size = size;
}
void *buffer_malloc(struct buffer *buf, size_t size) {
  buffer_init(buf, malloc(size), size);
  return buf->ptr;
}
void buffer_free(struct buffer *buf) {
  free(buf->ptr);
  buffer_init(buf, NULL, 0);
}
bool_t buffer_is_null(const struct buffer *buf) {
  assert(buf->ptr || buf->size == 0);
  return !buf->ptr;
}
void buffer_memcpy(struct buffer *dst, const struct buffer *src) {
  if (dst->ptr && src->ptr) {
    memcpy(dst->ptr, src->ptr, UTIL_MIN(dst->size, src->size));
  }
}
void buffer_memmove(struct buffer *dst, const struct buffer *src) {
  if (dst->ptr && src->ptr) {
    memmove(dst->ptr, src->ptr, UTIL_MIN(dst->size, src->size));
  }
}
void buffer_slice(struct buffer *buf, size_t offset, size_t size) {
  assert(offset + size <= buf->size);
  buf->ptr += offset;
  buf->size = size;
}
void buffer_slide(struct buffer *buf, size_t from, size_t to, size_t size) {
  struct buffer src = *buf, dst = *buf;
  buffer_slice(&src, from, size);
  buffer_slice(&dst, to, size);
  buffer_memmove(&dst, &src);
}
