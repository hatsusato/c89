#include "obj.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

static int json_obj_cmp(const void *lhs, const void *rhs) {
  const struct json_pair *l = lhs, *r = rhs;
  return util_strcmp(l->key, r->key);
}

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
void json_obj_insert(struct json *self, const char *key, struct json *val) {
  struct json_pair *pair = json_vec_search(self->vec, key, NULL, json_obj_cmp);
  if (pair) {
    pair->val = val;
  } else {
    json_vec_push(self->vec, key, val);
    json_vec_sort(self->vec, json_obj_cmp);
  }
}
