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
static void vector_malloc_data(struct vec *vec, size_t size, size_t count) {
  struct buffer buf;
  buffer_malloc(&buf, size * count);
  vec_init(vec, size, &buf);
}
static void vector_free_data(struct vec *vec) {
  struct buffer buf;
  buffer_init(&buf, vec->span.begin, vec->capacity);
  buffer_free(&buf);
}
static struct vec *vector_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec);
  return (struct vec *)buf.ptr;
}
static void vector_free(struct vec *vec) {
  struct buffer buf;
  BUFFER_INIT(&buf, vec);
  buffer_free(&buf);
}

void vec_init(struct vec *vec, size_t size, struct buffer *buf) {
  size = vector_aligned_size(size);
  vector_span_init(&vec->span, buf->ptr, size);
  vec->capacity = buf->size;
}
struct vec *vec_create(size_t size) {
  enum { vec_initial_count = 8 };
  struct vec *vec;
  size = vector_aligned_size(size);
  vec = vector_malloc();
  vector_malloc_data(vec, size, vec_initial_count);
  return vec;
}
void vec_delete(struct vec *vec) {
  vector_free_data(vec);
  vector_free(vec);
}
size_t vec_capacity(const struct vec *vec) {
  return vec->capacity / vec->span.size;
}
size_t vec_length(const struct vec *vec) {
  return vector_span_length(&vec->span);
}
bool_t vec_empty(const struct vec *vec) {
  return vec_length(vec) == 0;
}
void *vec_begin(struct vec *vec) {
  return vec->span.begin;
}
void *vec_end(struct vec *vec) {
  return vec->span.end;
}
void *vec_at(struct vec *vec, index_t i) {
  return vector_span_at(&vec->span, i);
}
