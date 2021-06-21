#include "buffer.h"

#include <stdlib.h>

void vector_buffer_malloc(struct vector_buffer *buf) {
  buf->ptr = malloc(buf->size);
}
void vector_buffer_free(struct vector_buffer *buf) {
  free(buf->ptr);
  buf->ptr = NULL;
  buf->size = 0;
}
