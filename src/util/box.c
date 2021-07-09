#include "box.h"

#include <stdlib.h>

#include "buffer.h"

struct box_data {
  size_t size;
  byte_t data[1];
};

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

struct box_data *box_data_new(size_t size) {
  struct box_data *box = malloc(sizeof(size_t) + size);
  box->size = size;
  return box;
}
void box_data_delete(struct box_data *box) {
  free(box);
}
