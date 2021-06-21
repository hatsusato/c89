#include "span.h"

static size_t vector_span_aligned_size(size_t size) {
  enum { vector_span_align = 8 };
  size += vector_span_align - 1;
  size /= vector_span_align;
  size *= vector_span_align;
  return size;
}

void vector_span_init(struct vector_span *span, byte_t *begin, size_t size) {
  span->begin = span->end = begin;
  span->size = vector_span_aligned_size(size);
}
