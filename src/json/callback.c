#include "callback.h"

#include "json.h"
#include "util/util.h"

struct json_callback {
  json_callback_t callback;
  struct json *args;
};

struct json_callback *json_callback_new(json_callback_t callback) {
  struct json_callback *self = util_malloc(sizeof(struct json_callback));
  self->callback = callback;
  self->args = json_new_obj();
  return self;
}
void json_callback_delete(struct json_callback *self) {
  json_delete(self->args);
  util_free(self);
}
struct json *json_callback_get(struct json_callback *self, const char *key) {
  return json_get(self->args, key);
}
void json_callback_insert(struct json_callback *self, const char *key,
                          struct json *val) {
  assert(json_is_obj(self->args));
  json_obj_insert(json_as_obj(self->args), key, val);
}
void json_callback_apply(struct json_callback *self) {
  self->callback(self->args);
}
