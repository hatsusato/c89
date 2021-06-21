#include "vec.h"

#include "span.h"
#include "utility/buffer.h"

void vec_init(struct vec *vec, size_t size, struct buffer *buf) {
  vector_span_init(&vec->span, buf->ptr, size);
  vec->capacity = buf->size;
}
