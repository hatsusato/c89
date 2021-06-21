#include "span.h"

#include <string.h>

static size_t vector_span_aligned_size(size_t size) {
  enum { vector_span_align = 8 };
  size += vector_span_align - 1;
  size /= vector_span_align;
  size *= vector_span_align;
  return size;
}
static void vector_span_memcpy(byte_t *ptr, const struct vector_buffer *src) {
  struct vector_buffer dst;
  dst.ptr = ptr;
  dst.size = src->size;
  vector_buffer_memcpy(&dst, src);
}

void vector_span_init(struct vector_span *span, byte_t *begin, size_t size) {
  span->begin = span->end = begin;
  span->size = vector_span_aligned_size(size);
}
size_t vector_span_length(struct vector_span *span) {
  return (span->end - span->begin) / span->size;
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
void vector_span_push_front(struct vector_span *span, byte_t *data,
                            size_t count) {
  span->begin -= span->size;
  memcpy(span->begin, data, count);
}
byte_t *vector_span_pop_front(struct vector_span *span) {
  byte_t *ptr = span->begin;
  span->begin += span->size;
  return ptr;
}
