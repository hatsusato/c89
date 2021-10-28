#include "obj.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_obj_new(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->str = NULL;
  self->vec = json_vec_new();
  return self;
}
void json_obj_delete(struct json *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
