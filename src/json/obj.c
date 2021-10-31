#include "obj.h"

#include "json.h"
#include "util/util.h"
#include "vec.h"

struct json_obj {
  struct json_vec *vec;
};

struct json_obj *json_obj_new(void) {
  struct json_obj *self = util_malloc(sizeof(struct json_obj));
  self->vec = json_vec_new();
  return self;
}
void json_obj_delete(struct json_obj *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
void json_obj_insert(struct json_obj *self, const char *key, struct json *val) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  if (pair) {
    pair->val = val;
  } else {
    json_vec_push(self->vec, key, val);
  }
}
struct json *json_obj_get(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  return pair ? pair->val : json_null();
}
bool_t json_obj_has(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  return pair ? true : false;
}
