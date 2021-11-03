#include "closure.h"

#include "json.h"
#include "util/util.h"

struct json_closure {
  json_closure_t closure;
  struct json *args;
};

struct json_closure *json_closure_new(json_closure_t closure) {
  struct json_closure *self = util_malloc(sizeof(struct json_closure));
  self->closure = closure;
  self->args = json_new_obj();
  return self;
}
void json_closure_delete(struct json_closure *self) {
  json_delete(self->args);
  util_free(self);
}
struct json *json_closure_args(struct json_closure *self) {
  return self->args;
}
struct json *json_closure_get(struct json_closure *self, const char *key) {
  return json_get(self->args, key);
}
void json_closure_insert(struct json_closure *self, const char *key,
                         struct json *val) {
  assert(json_is_obj(self->args));
  json_obj_insert(json_as_obj(self->args), key, val);
}
void json_closure_apply(struct json_closure *self) {
  self->closure(self);
}
