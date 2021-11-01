#include "factory.h"

#include "json.h"
#include "map.h"
#include "util/util.h"
#include "vec.h"

struct json_factory {
  struct json_vec *pool, *symbol;
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
  self->pool = json_vec_new();
  self->symbol = json_vec_new();
  return self;
}
void json_factory_delete(struct json_factory *self) {
  struct json_map map_pool = {json_factory_free_pool, NULL};
  struct json_map map_symbol = {json_factory_free_symbol, NULL};
  json_vec_foreach(self->symbol, &map_symbol);
  json_vec_delete(self->symbol);
  json_vec_foreach(self->pool, &map_pool);
  json_vec_delete(self->pool);
  util_free(self);
}
const char *json_factory_symbol(struct json_factory *self, const char *symbol) {
  struct json_pair *pair = json_vec_search(self->symbol, symbol);
  if (pair) {
    return json_pair_key(pair);
  } else {
    const char *dup = util_strdup(symbol);
    json_vec_push(self->symbol, dup, json_null());
    json_vec_sort(self->symbol);
    return dup;
  }
}
struct json *json_factory_int(struct json_factory *self, int num) {
  struct json *json = json_new_int(num);
  json_vec_push(self->pool, NULL, json);
  return json;
}
struct json *json_factory_str(struct json_factory *self, const char *str) {
  struct json *json = json_new_str(str);
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
