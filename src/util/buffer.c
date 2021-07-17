#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void buffer_init(struct buffer *self, const void *ptr, size_t size) {
  assert(ptr || size == 0);
  self->ptr = (void *)ptr;
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
void buffer_copy(struct buffer *self, size_t offset, const void *ptr,
                 size_t size) {
  assert(self->size >= offset + size);
  if (self->ptr && ptr && size > 0) {
    memcpy(self->ptr + offset, ptr, size);
  }
}
void buffer_slide(struct buffer *self, size_t src, size_t dst, size_t size) {
  assert(self->ptr);
  assert(src + size <= self->size);
  assert(dst + size <= self->size);
  memmove(self->ptr + dst, self->ptr + src, size);
}
