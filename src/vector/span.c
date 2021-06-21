#include "span.h"

#include <assert.h>

#include "utility/buffer.h"

void vector_span_init(struct vector_span *span, byte_t *ptr, align_t align) {
  span->begin = span->end = ptr;
  if (align > 0) {
    span->align = align;
  }
}
size_t vector_span_length(const struct vector_span *span) {
  size_t size = (span->end && span->begin) ? (span->end - span->begin) : 0;
  return size / span->align;
}
byte_t *vector_span_at(const struct vector_span *span, index_t i) {
  assert(span->begin);
  return span->begin + i * span->align;
}
void vector_span_push_back(struct vector_span *span, const struct buffer *buf) {
  if (buf) {
    struct buffer dst;
    buffer_init(&dst, span->end, span->align);
    buffer_memcpy(&dst, buf);
  }
  span->end += span->align;
}
void vector_span_pop_back(struct vector_span *span, struct buffer *buf) {
  span->end -= span->align;
  if (buf) {
    struct buffer src;
    buffer_init(&src, span->end, span->align);
    buffer_memcpy(buf, &src);
  }
}
void vector_span_push_front(struct vector_span *span,
                            const struct buffer *buf) {
  span->begin -= span->align;
  if (buf) {
    struct buffer dst;
    buffer_init(&dst, span->begin, span->align);
    buffer_memcpy(&dst, buf);
  }
}
void vector_span_pop_front(struct vector_span *span, struct buffer *buf) {
  if (buf) {
    struct buffer src;
    buffer_init(&src, span->begin, span->align);
    buffer_memcpy(buf, &src);
  }
  span->begin += span->align;
}
