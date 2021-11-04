#include "json.h"

#include "print.h"
#include "tag.h"
#include "util/util.h"
#include "visitor.h"

struct json_get_extra {
  const char *key;
  bool_t found;
  struct json *result;
};

bool_t json_is_null(struct json *self) {
  return json_tag(self) == JSON_TAG_NULL;
}
bool_t json_is_int(struct json *self) {
  return json_tag(self) == JSON_TAG_INT;
}
bool_t json_is_str(struct json *self) {
  return json_tag(self) == JSON_TAG_STR;
}
bool_t json_is_arr(struct json *self) {
  return json_tag(self) == JSON_TAG_ARR;
}
bool_t json_is_obj(struct json *self) {
  return json_tag(self) == JSON_TAG_OBJ;
}
struct json_int *json_as_int(struct json *self) {
  assert(json_is_int(self));
  return json_data(self);
}
struct json_str *json_as_str(struct json *self) {
  assert(json_is_str(self));
  return json_data(self);
}
struct json_arr *json_as_arr(struct json *self) {
  assert(json_is_arr(self));
  return json_data(self);
}
struct json_obj *json_as_obj(struct json *self) {
  assert(json_is_obj(self));
  return json_data(self);
}
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
  struct json_get_extra *extra = visitor->extra;
  if (!extra->found && json_is_obj(json)) {
    struct json_obj *obj = json_as_obj(json);
    if (json_obj_has(obj, extra->key)) {
      extra->result = json_obj_get(obj, extra->key);
      extra->found = true;
    }
  }
}
struct json *json_get(struct json *self, const char *key) {
  struct json_visitor visitor;
  struct json_get_extra extra;
  visitor.visitor = json_get_visitor;
  visitor.extra = &extra;
  extra.key = key;
  extra.found = false;
  extra.result = json_null();
  json_visit(&visitor, self);
  return extra.result;
}
const char *json_get_str(struct json *json) {
  return json_is_str(json) ? json_str_get(json_as_str(json)) : NULL;
}
