#include "span.h"

#include <assert.h>

#include "utility/buffer.h"

static void vector_span_copy_to(struct buffer *buf, void *ptr, size_t size) {
  struct buffer src;
  assert(size <= buf->size);
  buffer_init(&src, ptr, size);
  buffer_memcpy(buf, &src);
}
static void vector_span_copy_from(const struct buffer *buf, void *ptr,
                                  size_t size) {
  struct buffer dst;
  assert(size <= buf->size);
  buffer_init(&dst, ptr, size);
  buffer_memcpy(&dst, buf);
}

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
void vector_span_push_back(struct vector_span *span, size_t count,
                           const struct buffer *buf) {
  size_t size = span->align * count;
  if (buf) {
    vector_span_copy_from(buf, span->end, size);
  }
  span->end += size;
}
void vector_span_pop_back(struct vector_span *span, size_t count,
                          struct buffer *buf) {
  size_t size = span->align * count;
  assert(span->begin + size <= span->end);
  span->end -= size;
  if (buf) {
    vector_span_copy_to(buf, span->end, size);
  }
}
void vector_span_push_front(struct vector_span *span, size_t count,
                            const struct buffer *buf) {
  size_t size = span->align * count;
  span->begin -= size;
  if (buf) {
    vector_span_copy_from(buf, span->begin, size);
  }
}
void vector_span_pop_front(struct vector_span *span, size_t count,
                           struct buffer *buf) {
  size_t size = span->align * count;
  assert(span->begin + size <= span->end);
  if (buf) {
    vector_span_copy_to(buf, span->begin, size);
  }
  span->begin += size;
}
