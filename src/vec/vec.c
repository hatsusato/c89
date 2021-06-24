#include "vec.h"

#include <assert.h>

#include "type.h"

static struct vec *vec_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec);
  return (struct vec *)buf.ptr;
}
static void vec_free(struct vec *self) {
  struct buffer buf;
  BUFFER_INIT(&buf, self);
  buffer_free(&buf);
}
static index_t vec_buffer_capacity(const struct vec *self,
                                   const struct buffer *buf) {
  return buf->size / array_align(&self->array);
}

struct vec *vec_new(align_t align) {
  struct vec *self = vec_malloc();
  array_init(&self->array, align, NULL);
  return self;
}
void vec_delete(struct vec *self) {
  vec_reset(self);
  vec_free(self);
}
void vec_alloc(struct vec *self, align_t align, index_t count) {
  array_malloc(&self->array, align, count);
}
void vec_reset(struct vec *self) {
  array_free(&self->array);
}
void vec_reserve(struct vec *self, index_t count) {
  index_t cap = vec_capacity(self);
  count = (count == 0) ? 2 * cap : count;
  if (count > cap) {
    struct vec old = *self;
    vec_alloc(self, 0, count);
    vec_insert(self, 0, vec_length(&old), &old.array.buf);
    vec_reset(&old);
  }
}
index_t vec_capacity(const struct vec *self) {
  return array_capacity(&self->array);
}
index_t vec_length(const struct vec *self) {
  return array_length(&self->array);
}
void *vec_at(struct vec *self, index_t index) {
  return array_at(&self->array, index);
}
void vec_insert(struct vec *self, index_t index, index_t count,
                const struct buffer *buf) {
  index_t length = vec_length(self);
  index = (index == -1) ? length : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && length + count <= vec_capacity(self));
  assert(count <= vec_buffer_capacity(self, buf));
  array_insert(&self->array, index, count, buf);
}
void vec_remove(struct vec *self, index_t index, index_t count) {
  index_t length = vec_length(self);
  index = (index == -1) ? length - count : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && index + count <= length);
  array_remove(&self->array, index, count);
}

bool_t vec_empty(const struct vec *self) {
  return vec_length(self) == 0;
}
bool_t vec_full(const struct vec *self) {
  return vec_length(self) == vec_capacity(self);
}
void *vec_begin(struct vec *self) {
  return vec_at(self, 0);
}
void *vec_end(struct vec *self) {
  return vec_at(self, vec_length(self));
}
void vec_clear(struct vec *self) {
  vec_remove(self, 0, vec_length(self));
}
