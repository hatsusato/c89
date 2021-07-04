#include "box.h"

#include <stdlib.h>

#include "buffer.h"

void box_new(struct box *box, size_t size) {
  box->ptr = malloc(size);
  box->size = size;
}
void box_delete(struct box *box) {
  free(box->ptr);
  box->ptr = NULL;
  box->size = 0;
}
void box_buffer(struct box *box, struct buffer *buf) {
  buffer_init(buf, box->ptr, box->size);
}
void *box_ptr(const struct box *box) {
  return box->ptr;
}
size_t box_size(const struct box *box) {
  return box->size;
}
