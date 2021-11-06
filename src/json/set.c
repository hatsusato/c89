#include "set.h"

#include "json.h"
#include "map.h"
#include "pair.h"
#include "util/util.h"

struct json_set {
  struct json_obj *set;
};

static void json_set_del_map(struct json_map *map) {
  util_free((void *)json_map_key(map));
}

struct json_set *json_set_new(void) {
  struct json_set *self = util_malloc(sizeof(struct json_set));
  self->set = json_obj_new();
  json_obj_sort(self->set);
  return self;
}
void json_set_del(struct json_set *self) {
  json_obj_foreach(self->set, json_set_del_map, NULL);
  json_obj_del(self->set);
  util_free(self);
}
const char *json_set_insert(struct json_set *self, const char *symbol) {
  struct json_pair *pair = json_obj_find(self->set, symbol);
  if (pair) {
    return json_pair_key(pair);
  } else {
    const char *dup = util_strdup(symbol);
    json_obj_insert(self->set, dup, json_null());
    return dup;
  }
}
