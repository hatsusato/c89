#include "arr.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_arr_new(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_ARR;
  self->str = NULL;
  self->vec = json_vec_new();
  return self;
}
void json_arr_delete(struct json *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
