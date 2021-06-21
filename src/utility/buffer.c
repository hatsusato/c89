#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void buffer_init(struct buffer *buf, void *ptr, size_t size) {
  buf->ptr = ptr;
  buf->size = size;
}
void buffer_malloc(struct buffer *buf, size_t size) {
  buffer_init(buf, malloc(size), size);
}
void buffer_free(struct buffer *buf) {
  free(buf->ptr);
  buffer_init(buf, NULL, 0);
}
void buffer_memcpy(struct buffer *dst, const struct buffer *src) {
  assert(dst->size >= src->size);
  memcpy(dst->ptr, src->ptr, src->size);
}
