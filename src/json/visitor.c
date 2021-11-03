#include "visitor.h"

#include "json.h"
#include "map.h"
#include "util/util.h"

struct json_visitor {
  json_visitor_t visitor;
  const char *key;
  struct json *result;
  struct json_obj *parent;
  void *extra;
};

static void json_visitor_recurse(struct json_visitor *, struct json *);
static void json_visitor_visit_obj(struct json_map *map) {
  struct json_visitor *visitor = map->extra;
  if (util_streq(visitor->key, map->key)) {
    visitor->result = NULL;
    visitor->visitor(map->val, visitor->extra);
    if (visitor->result) {
      json_obj_insert(visitor->parent, map->key, visitor->result);
    }
  }
  json_visitor_recurse(visitor, map->val);
}
static void json_visitor_visit_arr(struct json_map *map) {
  json_visitor_recurse(map->extra, map->val);
}
static void json_visitor_recurse(struct json_visitor *self, struct json *json) {
  if (json_is_obj(json)) {
    struct json_obj *obj = json_as_obj(json);
    struct json_map map;
    map.map = json_visitor_visit_obj;
    map.extra = self;
    self->parent = obj;
    json_obj_foreach(obj, &map);
  } else if (json_is_arr(json)) {
    struct json_map map;
    map.map = json_visitor_visit_arr;
    map.extra = self;
    json_arr_foreach(json_as_arr(json), &map);
  }
}
void json_visitor_visit(json_visitor_t visitor, const char *key,
                        struct json *json, void *extra) {
  struct json_visitor self = {NULL, NULL, NULL, NULL, NULL};
  self.visitor = visitor;
  self.key = key;
  self.extra = extra;
  json_visitor_recurse(&self, json);
}
