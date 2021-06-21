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
void vector_malloc_data(struct vec *vec, size_t size, size_t count) {
  struct buffer buf;
  buf.size = size * count;
  buffer_malloc(&buf);
  vec_init(vec, size, &buf);
}
void vector_free_data(struct vec *vec) {
  struct buffer buf;
  buf.ptr = vec->span.begin;
  buf.size = vec->capacity;
  buffer_free(&buf);
}

void vec_init(struct vec *vec, size_t size, struct buffer *buf) {
  size = vector_aligned_size(size);
  vector_span_init(&vec->span, buf->ptr, size);
  vec->capacity = buf->size;
}
