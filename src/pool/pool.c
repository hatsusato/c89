#include "pool.h"

void pool_malloc(struct pool *self, size_t size) {
  buffer_malloc(&self->buf, size);
  self->offset = 0;
}
void pool_free(struct pool *self) {
  buffer_free(&self->buf);
  self->offset = 0;
}
