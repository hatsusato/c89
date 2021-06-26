#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "slice.h"
#include "util.h"

void buffer_init(struct buffer *self, void *ptr, size_t size) {
  self->ptr = ptr;
  self->size = size;
}
void *buffer_at(const struct buffer *self, size_t index) {
  return (index < self->size) ? self->ptr + index : NULL;
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
bool_t buffer_is_null(const struct buffer *self) {
  assert(self->ptr || self->size == 0);
  return !self->ptr;
}
void buffer_memcpy(struct buffer *self, const struct slice *slice) {
  size_t size = UTIL_MIN(self->size, slice_size(slice));
  if (!buffer_is_null(self) && !slice_is_null(slice) && size > 0) {
    memcpy(self->ptr, slice_at(slice, 0), size);
  }
}
void buffer_slice(struct buffer *self, size_t offset, size_t size) {
  assert(offset + size <= self->size);
  self->ptr += offset;
  self->size = size;
}
void buffer_slide(struct buffer *self, size_t src, size_t dst, size_t size) {
  assert(src + size <= self->size);
  assert(dst + size <= self->size);
  memmove(self->ptr + dst, self->ptr + src, size);
}
