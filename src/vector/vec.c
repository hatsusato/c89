#include "vec.h"

#include "span.h"
#include "utility/buffer.h"

static size_t vector_aligned_size(size_t size) {
  enum { vector_align = 8 };
  size += vector_align - 1;
  size /= vector_align;
  size *= vector_align;
  return size;
}
static void vector_malloc_data(struct vec *self, size_t size, size_t count) {
  struct buffer buf;
  buffer_malloc(&buf, size * count);
  vec_init(self, size, &buf);
}
static void vector_free_data(struct vec *self) {
  struct buffer buf;
  buffer_init(&buf, self->span.begin, self->capacity);
  buffer_free(&buf);
}
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

void vec_init(struct vec *self, size_t size, struct buffer *buf) {
  size = vector_aligned_size(size);
  vector_span_init(&self->span, buf->ptr, size);
  self->capacity = buf->size;
}
struct vec *vec_create(size_t size) {
  enum { vec_initial_count = 8 };
  struct vec *self;
  size = vector_aligned_size(size);
  self = vector_malloc();
  vector_malloc_data(self, size, vec_initial_count);
  return self;
}
void vec_delete(struct vec *self) {
  vector_free_data(self);
  vector_free(self);
}
size_t vec_capacity(const struct vec *self) {
  return self->capacity / self->span.size;
}
size_t vec_length(const struct vec *self) {
  return vector_span_length(&self->span);
}
bool_t vec_empty(const struct vec *self) {
  return vec_length(self) == 0;
}
bool_t vec_full(const struct vec *self) {
  return vec_length(self) == vec_capacity(self);
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
