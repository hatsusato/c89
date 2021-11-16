#include "util.h"

#include "json.h"
#include "map.h"
#include "print.h"
#include "tag.h"
#include "util/symbol.h"
#include "util/util.h"
#include "visitor.h"

struct json_find_extra {
  const char *key;
  struct json *result;
};

void json_print(struct json *self) {
  json_print_stdout(self);
}
void json_insert_str(struct json *self, const char *key, const char *val) {
  struct json *str = json_new_str(val);
  json_obj_insert(self, key, str);
  json_del(str);
}
bool_t json_has(struct json *self, const char *key) {
  return json_is_obj(self) ? json_obj_has(self, key) : false;
}
struct json *json_get(struct json *self, const char *key) {
  return json_is_obj(self) ? json_obj_get(self, key) : json_null();
}
const char *json_get_str(struct json *json) {
  return json_is_str(json) ? json_str_get(json) : NULL;
}
static void json_find_visitor(struct json_visitor *visitor, struct json *json) {
  struct json_find_extra *extra = json_visit_extra(visitor);
  if (json_has(json, extra->key)) {
    assert(json_is_obj(json));
    extra->result = json_obj_get(json, extra->key);
    json_visit_finish(visitor);
  }
  json_visit_foreach(visitor, json);
}
struct json *json_find(struct json *self, const char *key) {
  struct json_find_extra extra;
  extra.key = key;
  extra.result = json_null();
  json_visit(json_find_visitor, &extra, self);
  return extra.result;
}
static void json_find_identifier_visitor(struct json_visitor *visitor,
                                         struct json *json) {
  if (json_has(json, SYMBOL_DIRECT_DECLARATOR)) {
    while (!json_is_null(json)) {
      if (json_has(json, SYMBOL_IDENTIFIER)) {
        struct json_find_extra *extra = json_visit_extra(visitor);
        extra->result = json_get(json, SYMBOL_IDENTIFIER);
        json_visit_finish(visitor);
        return;
      } else if (json_has(json, SYMBOL_DECLARATOR)) {
        json = json_get(json, SYMBOL_DECLARATOR);
      } else {
        json = json_get(json, SYMBOL_DIRECT_DECLARATOR);
      }
    }
  } else {
    json_visit_foreach(visitor, json);
  }
}
struct json *json_find_identifier(struct json *json) {
  struct json_find_extra extra = {NULL, NULL};
  extra.result = json_null();
  json_visit(json_find_identifier_visitor, &extra, json);
  return extra.result;
}
static void json_append_map(struct json_map *map) {
  struct json *dst = json_map_extra(map);
  struct json *src = json_map_val(map);
  json_arr_push(dst, src);
}
void json_append(struct json *dst, struct json *src) {
  json_foreach(src, json_append_map, dst);
}
static void json_merge_map(struct json_map *map) {
  struct json *dst = json_map_extra(map);
  const char *key = json_map_key(map);
  struct json *val = json_map_val(map);
  json_obj_insert(dst, key, val);
}
void json_merge(struct json *dst, struct json *src) {
  json_foreach(src, json_merge_map, dst);
}
struct json *json_take(struct json *json, const char *key) {
  struct json *val = json_get(json, key);
  json_ref(val);
  return val;
}
