#include "vec.h"

#include "type.h"
#include "util/util.h"

struct json_vec *json_vec_new(void) {
  struct json_vec *self = util_malloc(sizeof(struct json_vec));
  self->array.base = NULL;
  self->array.count = self->capacity = 0;
  return self;
}
void json_vec_delete(struct json_vec *self) {
  util_free(self->array.base);
  util_free(self);
}
