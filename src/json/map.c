#include "map.h"

#include "json.h"
#include "pair.h"
#include "tag.h"
#include "vec.h"

struct json_map {
  json_map_t map;
  void *extra;
  bool_t finished;
  index_t index;
  const char *key;
  struct json *val;
};

void *json_map_extra(struct json_map *self) {
  return self->extra;
}
void json_map_finish(struct json_map *self) {
  self->finished = true;
}
index_t json_map_index(struct json_map *self) {
  return self->index;
}
const char *json_map_key(struct json_map *self) {
  return self->key;
}
struct json *json_map_val(struct json_map *self) {
  return self->val;
}
void json_map_foreach(json_map_t map, void *extra, struct json_vec *vec) {
  struct json_map self;
  index_t i, count = json_vec_count(vec);
  self.map = map;
  self.extra = extra;
  self.finished = false;
  for (i = 0; i < count && !self.finished; i++) {
    struct json_pair *pair = json_vec_at(vec, i);
    self.index = i;
    self.key = json_pair_key(pair);
    self.val = json_pair_val(pair);
    map(&self);
  }
}
void json_foreach(struct json *json, json_map_t map, void *extra) {
  switch (json_tag(json)) {
  case JSON_TAG_ARR:
    json_arr_foreach(json_as_arr(json), map, extra);
    break;
  case JSON_TAG_OBJ:
    json_obj_foreach(json_as_obj(json), map, extra);
    break;
  default:
    break;
  }
}
