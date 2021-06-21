#include "span.h"

#include <assert.h>

#include "utility/buffer.h"

static void vector_span_memcpy(byte_t *ptr, const struct buffer *src) {
  struct buffer dst;
  dst.ptr = ptr;
  dst.size = src->size;
  buffer_memcpy(&dst, src);
}

void vector_span_init(struct vector_span *span, byte_t *begin, size_t size) {
  span->begin = span->end = begin;
  span->size = size;
}
size_t vector_span_length(const struct vector_span *span) {
  return (span->end - span->begin) / span->size;
}
void vector_span_push_back(struct vector_span *span, const struct buffer *buf) {
  assert(span->size >= buf->size);
  vector_span_memcpy(span->end, buf);
  span->end += span->size;
}
byte_t *vector_span_pop_back(struct vector_span *span) {
  span->end -= span->size;
  return span->end;
}
void vector_span_push_front(struct vector_span *span,
                            const struct buffer *buf) {
  assert(span->size >= buf->size);
  span->begin -= span->size;
  vector_span_memcpy(span->begin, buf);
}
byte_t *vector_span_pop_front(struct vector_span *span) {
  byte_t *ptr = span->begin;
  span->begin += span->size;
  return ptr;
}
