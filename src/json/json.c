#include "json.h"

#include "print.h"
#include "tag.h"
#include "util/util.h"

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
