#include "array.h"

#include <assert.h>

static void array_slide(struct array *self, index_t index, index_t count) {
  align_t align = array_align(self);
  index_t length = array_length(self);
  size_t from = index * align;
  size_t to = (index + count) * align;
  size_t size = (length - index) * align;
  buffer_slide(&self->buf, from, to, size);
  self->len += count;
}

void array_init(struct array *self, align_t align) {
  assert(align > 0);
  self->align = align;
  buffer_init(&self->buf, NULL, 0);
  self->len = 0;
}
void array_malloc(struct array *self, index_t count) {
  struct buffer buf;
  assert(0 <= count);
  buffer_malloc(&buf, self->align * count);
  array_set(self, &buf);
}
void array_free(struct array *self) {
  buffer_free(&self->buf);
  self->len = 0;
}
void array_get(struct array *self, struct buffer *buf) {
  *buf = self->buf;
}
void array_set(struct array *self, const struct buffer *buf) {
  self->buf = *buf;
  self->len = 0;
}
bool_t array_is_null(const struct array *self) {
  bool_t ret = buffer_is_null(&self->buf);
  assert(!ret || self->len == 0);
  return ret;
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
  index_t length = array_length(self);
  index += index < 0 ? length : 0;
  assert(0 <= index && index < length);
  return self->buf.ptr + index * array_align(self);
}
void array_insert(struct array *self, index_t index, index_t count,
                  const struct buffer *buf) {
  struct buffer src = *buf, dst = self->buf;
  align_t align = array_align(self);
  assert(0 <= index && 0 <= count);
  assert(index <= array_length(self));
  array_slide(self, index, count);
  buffer_slice(&src, 0, count * align);
  buffer_slice(&dst, index * align, count * align);
  buffer_memcpy(&dst, buf);
}
void array_remove(struct array *self, index_t index, index_t count) {
  assert(0 <= index && 0 <= count);
  assert(index + count <= array_length(self));
  array_slide(self, index + count, -count);
}
