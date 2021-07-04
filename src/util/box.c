#include "box.h"

#include <stdlib.h>

void box_new(struct box *box, size_t size) {
  box->ptr = malloc(size);
  box->size = size;
}
void box_delete(struct box *box) {
  free(box->ptr);
  box->ptr = NULL;
  box->size = 0;
}
