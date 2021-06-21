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

void vec_init(struct vec *vec, size_t size, struct buffer *buf) {
  size = vector_aligned_size(size);
  vector_span_init(&vec->span, buf->ptr, size);
  vec->capacity = buf->size;
}
