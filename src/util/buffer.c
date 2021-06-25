#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void buffer_init(struct buffer *self, void *ptr, size_t size) {
  self->ptr = ptr;
  self->size = size;
}
void *buffer_at(const struct buffer *self, size_t index) {
  assert(index < self->size);
  return self->ptr + index;
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
void buffer_slice(struct buffer *self, size_t offset, size_t size) {
  assert(offset + size <= self->size);
  self->ptr += offset;
  self->size = size;
}
void buffer_slide(struct buffer *self, size_t from, size_t to, size_t size) {
  struct buffer src = *self, dst = *self;
  buffer_slice(&src, from, size);
  buffer_slice(&dst, to, size);
  buffer_memmove(&dst, &src);
}
void buffer_sort(struct buffer *self, index_t count, align_t align, cmp_t cmp) {
  assert(0 <= count && count * align <= self->size);
  qsort(self->ptr, count, align, cmp);
}
void *buffer_search(const struct buffer *self, const void *key, index_t count,
                    align_t align, cmp_t cmp) {
  assert(0 <= count && count * align <= self->size);
  return bsearch(key, self->ptr, count, align, cmp);
}
