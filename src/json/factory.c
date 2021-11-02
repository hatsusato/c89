#include "factory.h"

#include "closure.h"
#include "json.h"
#include "util/util.h"
#include "vec.h"

struct json_factory {
  struct json_obj *symbol;
  struct json_arr *pool;
};

static void json_factory_free(struct json *args) {
  struct json *key = json_get(args, "key");
  struct json *val = json_get(args, "val");
  if (json_is_str(key)) {
    struct json_str *str = json_as_str(key);
    util_free((void *)json_str_get(str));
  }
  json_delete(val);
}

struct json_factory *json_factory_new(void) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->symbol = json_obj_new();
  self->pool = json_arr_new();
  json_obj_sort(self->symbol);
  return self;
}
void json_factory_delete(struct json_factory *self) {
  struct json_closure *map = json_closure_new(json_factory_free);
  struct json *key = json_new_str("");
  json_arr_map(self->pool, map);
  json_closure_insert(map, "key", key);
  json_obj_map(self->symbol, map);
  json_arr_delete(self->pool);
  json_obj_delete(self->symbol);
  util_free(self);
  json_delete(key);
  json_closure_delete(map);
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
