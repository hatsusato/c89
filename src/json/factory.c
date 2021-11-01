#include "factory.h"

#include "json.h"
#include "map.h"
#include "util/util.h"
#include "vec.h"

struct json_factory {
  struct json_arr *pool;
  struct json_obj *symbol;
};

static void json_factory_free_pool(const char *key, struct json *val,
                                   void *extra) {
  json_delete(val);
  UTIL_UNUSED(key);
  UTIL_UNUSED(extra);
}
static void json_factory_free_symbol(const char *key, struct json *val,
                                     void *extra) {
  util_free((void *)key);
  UTIL_UNUSED(val);
  UTIL_UNUSED(extra);
}

struct json_factory *json_factory_new(void) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->pool = json_arr_new();
  self->symbol = json_obj_new();
  json_obj_sort(self->symbol);
  return self;
}
void json_factory_delete(struct json_factory *self) {
  struct json_map map_pool = {json_factory_free_pool, NULL};
  struct json_map map_symbol = {json_factory_free_symbol, NULL};
  json_obj_foreach(self->symbol, &map_symbol);
  json_arr_foreach(self->pool, &map_pool);
  json_obj_delete(self->symbol);
  json_arr_delete(self->pool);
  util_free(self);
}
const char *json_factory_symbol(struct json_factory *self, const char *symbol) {
  struct json_pair *pair = json_obj_find(self->symbol, symbol);
  if (pair) {
    return json_pair_key(pair);
  } else {
    const char *dup = util_strdup(symbol);
    json_obj_insert(self->symbol, dup, json_null());
    return dup;
  }
}
struct json *json_factory_int(struct json_factory *self, int num) {
  struct json *json = json_new_int(num);
  json_arr_push(self->pool, json);
  return json;
}
struct json *json_factory_str(struct json_factory *self, const char *str) {
  struct json *json = json_new_str(str);
  json_arr_push(self->pool, json);
  return json;
}
struct json *json_factory_arr(struct json_factory *self) {
  struct json *json = json_new_arr();
  json_arr_push(self->pool, json);
  return json;
}
struct json *json_factory_obj(struct json_factory *self) {
  struct json *json = json_new_obj();
  json_arr_push(self->pool, json);
  return json;
}
