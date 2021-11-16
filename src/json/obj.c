#include "obj.h"

#include "map.h"
#include "new.h"
#include "pair.h"
#include "util/util.h"
#include "vec.h"

struct json_obj {
  struct json_vec *vec;
  bool_t sorted;
};

struct json_obj *json_obj_new(void) {
  struct json_obj *self = util_malloc(sizeof(struct json_obj));
  self->vec = json_vec_new();
  self->sorted = false;
  return self;
}
void json_obj_del(struct json *self) {
  json_vec_del(json_as_obj(self)->vec);
  util_free(json_as_obj(self));
}
index_t json_obj_count(struct json *self) {
  return json_vec_count(json_as_obj(self)->vec);
}
void json_obj_insert(struct json *self, const char *key, struct json *val) {
  struct json_pair *pair = json_obj_find(self, key);
  if (pair) {
    json_del(json_pair_val(pair));
    json_ref(val);
    json_pair_set(pair, key, val);
  } else {
    json_vec_push(json_as_obj(self)->vec, key, val);
    if (json_as_obj(self)->sorted) {
      json_vec_sort(json_as_obj(self)->vec);
    }
  }
}
struct json *json_obj_get(struct json *self, const char *key) {
  struct json_pair *pair = json_obj_find(self, key);
  return pair ? json_pair_val(pair) : json_null();
}
bool_t json_obj_has(struct json *self, const char *key) {
  struct json_pair *pair = json_obj_find(self, key);
  return UTIL_BOOL(pair);
}
struct json_pair *json_obj_find(struct json *self, const char *key) {
  if (json_as_obj(self)->sorted) {
    return json_vec_search(json_as_obj(self)->vec, key);
  } else {
    return json_vec_find(json_as_obj(self)->vec, key);
  }
}
void json_obj_sort(struct json *self) {
  json_as_obj(self)->sorted = true;
  json_vec_sort(json_as_obj(self)->vec);
}
void json_obj_foreach(struct json *self, json_map_t map, void *extra) {
  json_map_foreach(map, extra, json_as_obj(self)->vec);
}
