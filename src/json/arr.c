#include "arr.h"

#include "map.h"
#include "new.h"
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
void json_arr_del(struct json *self) {
  json_vec_del(json_as_arr(self)->vec);
  util_free(json_as_arr(self));
}
index_t json_arr_count(struct json *self) {
  return json_vec_count(json_as_arr(self)->vec);
}
struct json *json_arr_at(struct json *self, index_t index) {
  struct json_pair *pair = json_vec_at(json_as_arr(self)->vec, index);
  return pair ? json_pair_val(pair) : json_null();
}
void json_arr_push(struct json *self, struct json *val) {
  json_vec_push(json_as_arr(self)->vec, NULL, val);
}
void json_arr_foreach(struct json *self, json_map_t map, void *extra) {
  json_map_foreach(map, extra, json_as_arr(self)->vec);
}
