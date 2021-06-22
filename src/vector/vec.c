#include "vec.h"

#include <assert.h>

#include "type.h"

static struct vec *vector_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec);
  return (struct vec *)buf.ptr;
}
static void vector_free(struct vec *self) {
  struct buffer buf;
  BUFFER_INIT(&buf, self);
  buffer_free(&buf);
}
static index_t vector_buffer_capacity(const struct vec *self,
                                      const struct buffer *buf) {
  return buf->size / self->align;
}
static void vector_init_buffer(struct vec *self, index_t begin, index_t end,
                               struct buffer *buf) {
  buffer_init(buf, vec_at(self, begin), (end - begin) * self->align);
}
static void vector_slide(struct vec *self, index_t index, index_t count) {
  struct buffer src, dst;
  index_t length = vec_length(self);
  if (0 <= index && index < length) {
    vector_init_buffer(self, index, length, &src);
    vector_init_buffer(self, index + count, length + count, &dst);
    buffer_memmove(&dst, &src);
  }
}

struct vec *vec_new(align_t align) {
  struct vec *self = vector_malloc();
  vec_init(self, align);
  return self;
}
void vec_delete(struct vec *self) {
  vec_reset(self);
  vector_free(self);
}
void vec_init(struct vec *self, align_t align) {
  self->align = align;
  buffer_init(&self->buf, NULL, 0);
  self->length = 0;
}
void vec_alloc(struct vec *self, index_t count) {
  buffer_malloc(&self->buf, self->align * count);
  self->length = 0;
}
void vec_reset(struct vec *self) {
  buffer_free(&self->buf);
  self->length = 0;
}
void vec_reserve(struct vec *self, index_t count) {
  index_t cap = vec_capacity(self);
  count = (count == 0) ? 2 * cap : count;
  if (count > cap) {
    struct vec old = *self;
    vec_alloc(self, count);
    vec_insert(self, 0, vec_length(&old), &old.buf);
    vec_reset(&old);
  }
}
index_t vec_capacity(const struct vec *self) {
  return vector_buffer_capacity(self, &self->buf);
}
index_t vec_length(const struct vec *self) {
  return self->length;
}
void *vec_at(struct vec *self, index_t i) {
  return self->buf.ptr ? self->buf.ptr + i * self->align : NULL;
}
void vec_insert(struct vec *self, index_t index, index_t count,
                const struct buffer *buf) {
  struct buffer dst;
  index_t length = vec_length(self);
  index = (index == -1) ? length : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && length + count <= vec_capacity(self));
  assert(count <= vector_buffer_capacity(self, buf));
  vector_slide(self, index, count);
  vector_init_buffer(self, index, index + count, &dst);
  buffer_memcpy(&dst, buf);
  self->length += count;
}
void vec_remove(struct vec *self, index_t index, index_t count) {
  index_t length = vec_length(self);
  index = (index == -1) ? length - count : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && index + count <= length);
  vector_slide(self, index + count, -count);
  self->length -= count;
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
