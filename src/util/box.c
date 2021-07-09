#include "box.h"

#include <stdlib.h>

#include "buffer.h"

struct box {
  size_t size;
  byte_t data[1];
};

struct box *box_new(size_t size) {
  struct box *box = malloc(sizeof(size_t) + size);
  box->size = size;
  return box;
}
void box_delete(struct box *box) {
  free(box);
}
void box_buffer(struct box *box, struct buffer *buf) {
  buffer_init(buf, box_ptr(box), box_size(box));
}
void *box_ptr(const struct box *box) {
  const byte_t *ptr = box->data;
  return (void *)ptr;
}
size_t box_size(const struct box *box) {
  return box->size;
}
