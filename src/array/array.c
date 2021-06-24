#include "array.h"

#include <assert.h>

static void array_slide(struct array *self, index_t index, index_t count) {
  align_t align = array_align(self);
  index_t length = array_length(self);
  size_t from = index * align;
  size_t to = (index + count) * align;
  size_t size = (length - index) * align;
  assert(0 <= index && index <= length);
  buffer_slide(&self->buf, from, to, size);
  self->len += count;
}

void array_init(struct array *self, align_t align, struct buffer *buf) {
  if (align != 0) {
    self->align = align;
  }
  if (buf) {
    self->buf = *buf;
  } else {
    buffer_init(&self->buf, NULL, 0);
  }
  self->len = 0;
}
void array_malloc(struct array *self, align_t align, index_t count) {
  struct buffer buf;
  assert(align > 0 || self->align > 0);
  assert(0 <= count);
  align = (align == 0) ? self->align : align;
  buffer_malloc(&buf, align * count);
  array_init(self, align, &buf);
}
void array_free(struct array *self) {
  buffer_free(&self->buf);
  self->len = 0;
}
align_t array_align(const struct array *self) {
  return self->align;
}
index_t array_capacity(const struct array *self) {
  return self->buf.size / array_align(self);
}
index_t array_length(const struct array *self) {
  return self->len;
}
void *array_at(struct array *self, index_t index) {
  assert(0 <= index && index < array_length(self));
  return self->buf.ptr + index * array_align(self);
}
void array_insert(struct array *self, index_t index, index_t count,
                  const struct buffer *buf) {
  struct buffer src = *buf, dst = self->buf;
  align_t align = array_align(self);
  assert(0 <= index && index <= array_length(self));
  assert(0 <= count);
  array_slide(self, index, count);
  buffer_slice(&src, 0, count * align);
  buffer_slice(&dst, index * align, count * align);
  buffer_memcpy(&dst, buf);
}
void array_remove(struct array *self, index_t index, index_t count) {
  assert(0 <= index && index <= array_length(self));
  assert(0 <= count);
  array_slide(self, index + count, -count);
}
