#include "map.h"

#include "pair.h"
#include "vec.h"

struct json_map {
  json_map_t map;
  void *extra;
  index_t index;
  const char *key;
  struct json *val;
};

void *json_map_extra(struct json_map *self) {
  return self->extra;
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
  for (i = 0; i < count; i++) {
    struct json_pair *pair = json_vec_at(vec, i);
    self.map = map;
    self.extra = extra;
    self.index = i;
    self.key = json_pair_key(pair);
    self.val = json_pair_val(pair);
    map(&self);
  }
}
