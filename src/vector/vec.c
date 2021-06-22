#include "vec.h"

#include <assert.h>

#include "span.h"
#include "utility/type.h"

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
  self->align = self->span.align = align;
  vector_span_init(&self->span, NULL);
  buffer_init(&self->buf, NULL, 0);
  self->length = 0;
  return self;
}
void vec_delete(struct vec *self) {
  vec_reset(self);
  vector_free(self);
}
void vec_alloc(struct vec *self, index_t count) {
  buffer_malloc(&self->buf, self->align * count);
  vector_span_init(&self->span, self->buf.ptr);
  self->length = 0;
}
void vec_reset(struct vec *self) {
  buffer_free(&self->buf);
  vector_span_init(&self->span, NULL);
  self->length = 0;
}
void vec_reserve(struct vec *self, index_t count) {
  count = (count == 0) ? 2 * vec_capacity(self) : count;
  if (count > vec_capacity(self)) {
    size_t length = vec_length(self);
    struct buffer old = self->buf, src;
    vector_init_buffer(self, 0, length, &src);
    vec_alloc(self, count);
    buffer_memcpy(&self->buf, &src);
    self->length = length;
    buffer_free(&old);
  }
}
index_t vec_capacity(const struct vec *self) {
  return self->buf.size / self->align;
}
index_t vec_length(const struct vec *self) {
  return self->length;
}
void *vec_at(struct vec *self, index_t i) {
  return vector_span_at(&self->span, i);
}
void vec_insert(struct vec *self, index_t index, index_t count,
                const struct buffer *buf) {
  struct buffer dst;
  index_t length = vec_length(self);
  size_t size = count * self->align;
  index = (index == -1) ? length : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && length + count <= vec_capacity(self));
  assert(size <= buf->size);
  vector_slide(self, index, count);
  vector_init_buffer(self, index, index + count, &dst);
  buffer_memcpy(&dst, buf);
  self->span.end += size;
  self->length += count;
}
void vec_remove(struct vec *self, index_t index, index_t count) {
  index_t length = vec_length(self);
  size_t size = count * self->align;
  index = (index == -1) ? length - count : index;
  assert(0 <= index && index <= length);
  assert(0 <= count && index + count <= length);
  vector_slide(self, index + count, -count);
  self->span.end -= size;
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
