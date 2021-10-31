#include "arr.h"

#include "json.h"
#include "pair.h"
#include "util/util.h"
#include "vec.h"

struct json_arr {
  struct json_vec *vec;
};

struct json_arr *json_arr_new(void) {
  struct json_arr *self = util_malloc(sizeof(struct json_arr));
  self->vec = json_vec_new();
  return self;
}
void json_arr_delete(struct json_arr *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
index_t json_arr_count(struct json_arr *self) {
  return json_vec_count(self->vec);
}
struct json *json_arr_at(struct json_arr *self, index_t index) {
  struct json_pair *pair = json_vec_at(self->vec, index);
  return pair ? pair->val : json_null();
}
void json_arr_push(struct json_arr *self, struct json *val) {
  json_vec_push(self->vec, NULL, val);
}
