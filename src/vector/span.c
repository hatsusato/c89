#include "span.h"

#include "utility/buffer.h"

void vector_span_init(struct vector_span *span, byte_t *begin, size_t size) {
  span->begin = span->end = begin;
  span->size = size;
}
size_t vector_span_length(const struct vector_span *span) {
  return (span->end - span->begin) / span->size;
}
void vector_span_push_back(struct vector_span *span, const struct buffer *buf) {
  struct buffer dst;
  buffer_init(&dst, span->end, span->size);
  buffer_memcpy(&dst, buf);
  span->end += span->size;
}
void vector_span_pop_back(struct vector_span *span, struct buffer *buf) {
  struct buffer src;
  span->end -= span->size;
  buffer_init(&src, span->end, span->size);
  buffer_memcpy(buf, &src);
}
void vector_span_push_front(struct vector_span *span,
                            const struct buffer *buf) {
  struct buffer dst;
  span->begin -= span->size;
  buffer_init(&dst, span->begin, span->size);
  buffer_memcpy(&dst, buf);
}
void vector_span_pop_front(struct vector_span *span, struct buffer *buf) {
  struct buffer src;
  buffer_init(&src, span->begin, span->size);
  buffer_memcpy(buf, &src);
  span->begin += span->size;
}
