#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void buffer_init(struct buffer *self, void *ptr, size_t size) {
  assert(ptr || size == 0);
  self->ptr = ptr;
  self->size = size;
}
void *buffer_at(const struct buffer *self, size_t index) {
  if (index < self->size) {
    assert(self->ptr);
    return self->ptr + index;
  } else {
    return NULL;
  }
}
size_t buffer_size(const struct buffer *self) {
  return self->size;
}
void *buffer_malloc(struct buffer *self, size_t size) {
  buffer_init(self, malloc(size), size);
  return self->ptr;
}
void buffer_free(struct buffer *self) {
  free(self->ptr);
  buffer_init(self, NULL, 0);
}
void buffer_memcpy(struct buffer *self, const struct buffer *buf) {
  assert(self->size >= buf->size);
  if (self->ptr && buf->ptr) {
    memcpy(self->ptr, buf->ptr, buf->size);
  }
}
void buffer_slice(struct buffer *self, size_t offset, size_t size) {
  assert(self->ptr);
  assert(offset + size <= self->size);
  self->ptr += offset;
  self->size = size;
}
void buffer_slide(struct buffer *self, size_t src, size_t dst, size_t size) {
  assert(self->ptr);
  assert(src + size <= self->size);
  assert(dst + size <= self->size);
  memmove(self->ptr + dst, self->ptr + src, size);
}
