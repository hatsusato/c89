#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void vector_buffer_malloc(struct vector_buffer *buf) {
  buf->ptr = malloc(buf->size);
}
void vector_buffer_free(struct vector_buffer *buf) {
  free(buf->ptr);
  buf->ptr = NULL;
  buf->size = 0;
}
void vector_buffer_memcpy(struct vector_buffer *dst,
                          const struct vector_buffer *src) {
  assert(dst->size >= src->size);
  memcpy(dst->ptr, src->ptr, src->size);
}
