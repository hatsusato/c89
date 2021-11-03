#include "json.h"

#include "print.h"
#include "tag.h"
#include "type.h"
#include "util/util.h"

struct json *json_new_int(int num) {
  return json_alloc(JSON_TAG_INT, json_int_new(num));
}
struct json *json_new_str(const char *str) {
  return json_alloc(JSON_TAG_STR, json_str_new(str));
}
struct json *json_new_arr(void) {
  return json_alloc(JSON_TAG_ARR, json_arr_new());
}
struct json *json_new_obj(void) {
  return json_alloc(JSON_TAG_OBJ, json_obj_new());
}
void json_delete(struct json *self) {
  void *data = json_data(self);
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return;
  case JSON_TAG_INT:
    json_int_delete(data);
    break;
  case JSON_TAG_STR:
    json_str_delete(data);
    break;
  case JSON_TAG_ARR:
    json_arr_delete(data);
    break;
  case JSON_TAG_OBJ:
    json_obj_delete(data);
    break;
  default:
    break;
  }
  json_free(self);
}
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
