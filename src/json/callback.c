#include "callback.h"

#include "obj.h"
#include "util/util.h"

struct json_callback {
  json_callback_t callback;
  struct json_obj *args;
};

struct json_callback *json_callback_new(json_callback_t callback) {
  struct json_callback *self = util_malloc(sizeof(struct json_callback));
  self->callback = callback;
  self->args = json_obj_new();
  return self;
}
void json_callback_delete(struct json_callback *self) {
  json_obj_delete(self->args);
  util_free(self);
}
