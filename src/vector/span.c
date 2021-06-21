#include "span.h"

#include <string.h>

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
void vector_span_push_back(struct vector_span *span, byte_t *data,
                           size_t count) {
  memcpy(span->end, data, count);
  span->end += span->size;
}
byte_t *vector_span_pop_back(struct vector_span *span) {
  span->end -= span->size;
  return span->end;
}
