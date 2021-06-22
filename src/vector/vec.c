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

void vec_alloc(struct vec *self, index_t count) {
  buffer_malloc(&self->buf, self->align * count);
  vector_span_init(&self->span, self->buf.ptr);
  self->length = vector_span_length(&self->span);
}
void vec_reset(struct vec *self) {
  buffer_free(&self->buf);
  vector_span_init(&self->span, NULL);
  self->length = vector_span_length(&self->span);
}
struct vec *vec_new(align_t align) {
  struct vec *self = vector_malloc();
  self->align = self->span.align = align;
  vector_span_init(&self->span, NULL);
  buffer_init(&self->buf, NULL, 0);
  self->length = vector_span_length(&self->span);
  return self;
}
void vec_delete(struct vec *self) {
  vec_reset(self);
  vector_free(self);
}
void vec_reserve(struct vec *self, index_t count) {
  if (count == 0) {
    count = 2 * vec_capacity(self);
  }
  if (count > vec_capacity(self)) {
    size_t len = vec_length(self);
    struct buffer old = self->buf;
    vec_alloc(self, count);
    vector_span_push_back(&self->span, len, &old);
    self->length = vector_span_length(&self->span);
    buffer_free(&old);
  }
}
index_t vec_capacity(const struct vec *self) {
  return self->buf.size / self->align;
}
index_t vec_length(const struct vec *self) {
  return vector_span_length(&self->span);
}
bool_t vec_empty(const struct vec *self) {
  return vec_length(self) == 0;
}
bool_t vec_full(const struct vec *self) {
  return vec_length(self) == (index_t)vec_capacity(self);
}
void *vec_begin(struct vec *self) {
  return self->span.begin;
}
void *vec_end(struct vec *self) {
  return self->span.end;
}
void *vec_at(struct vec *self, index_t i) {
  return vector_span_at(&self->span, i);
}
void vec_pop(struct vec *self, struct buffer *buf) {
  if (!vec_empty(self)) {
    vector_span_pop_back(&self->span, 1, buf);
    self->length = vector_span_length(&self->span);
  }
}
void vec_clear(struct vec *self) {
  vector_span_pop_back(&self->span, vec_length(self), NULL);
  self->length = vector_span_length(&self->span);
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
