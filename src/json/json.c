#include "json.h"

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
