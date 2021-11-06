#include "util.h"

#include "json.h"
#include "print.h"
#include "tag.h"
#include "util/util.h"
#include "visitor.h"

struct json_get_extra {
  const char *key;
  struct json *result;
};

void json_print(struct json *self) {
  json_print_stdout(self);
}
void json_set(struct json *self, const char *key, struct json *val) {
  if (json_is_obj(self)) {
    json_obj_insert(json_as_obj(self), key, val);
  }
}
bool_t json_has(struct json *self, const char *key) {
  return json_is_obj(self) ? json_obj_has(json_as_obj(self), key) : false;
}
static void json_get_visitor(struct json_visitor *visitor, struct json *json) {
  struct json_get_extra *extra = json_visit_extra(visitor);
  if (json_has(json, extra->key)) {
    assert(json_is_obj(json));
    extra->result = json_obj_get(json_as_obj(json), extra->key);
    json_visit_finish(visitor);
  }
  json_visit_foreach(visitor, json);
}
struct json *json_get(struct json *self, const char *key) {
  struct json_get_extra extra;
  extra.key = key;
  extra.result = json_null();
  json_visit(json_get_visitor, &extra, self);
  return extra.result;
}
const char *json_get_str(struct json *json) {
  return json_is_str(json) ? json_str_get(json_as_str(json)) : NULL;
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
