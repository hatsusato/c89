#include "box.h"

#include <stdlib.h>

#include "buffer.h"

struct box_data {
  size_t size;
  byte_t data[1];
};

struct box_data *box_data_new(size_t size) {
  struct box_data *box = malloc(sizeof(size_t) + size);
  box->size = size;
  return box;
}
void box_data_delete(struct box_data *box) {
  free(box);
}
void box_data_buffer(struct box_data *box, struct buffer *buf) {
  buffer_init(buf, box_data_ptr(box), box_data_size(box));
}
void *box_data_ptr(const struct box_data *box) {
  const byte_t *ptr = box->data;
  return (void *)ptr;
}
size_t box_data_size(const struct box_data *box) {
  return box->size;
}
