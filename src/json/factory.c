#include "factory.h"

#include "json.h"
#include "util/util.h"
#include "vec.h"

struct json_factory {
  struct json_vec *pool, *symbol;
};

static void json_factory_free(const char *key, struct json *val, void *extra) {
  if (extra) {
    assert(val);
    json_delete(val);
  } else {
    assert(key);
    util_free((void *)key);
  }
}

struct json_factory *json_factory_new(void) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->pool = json_vec_new();
  self->symbol = json_vec_new();
  return self;
}
void json_factory_delete(struct json_factory *self) {
  struct json_map map = {json_factory_free, NULL};
  json_vec_foreach(self->symbol, &map);
  json_vec_delete(self->symbol);
  map.extra = &map;
  json_vec_foreach(self->pool, &map);
  json_vec_delete(self->pool);
  util_free(self);
}
struct json *json_factory_str(struct json_factory *self, const char *str) {
  struct json *json = json_new_str(str);
  assert(str);
  json_vec_push(self->pool, NULL, json);
  return json;
}
struct json *json_factory_arr(struct json_factory *self) {
  struct json *json = json_new_arr();
  json_vec_push(self->pool, NULL, json);
  return json;
}
struct json *json_factory_obj(struct json_factory *self) {
  struct json *json = json_new_obj();
  json_vec_push(self->pool, NULL, json);
  return json;
}
