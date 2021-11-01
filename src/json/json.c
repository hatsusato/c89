#include "json.h"

#include "printer.h"
#include "tag.h"
#include "type.h"
#include "util/util.h"

struct json *json_new_int(int num) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_INT;
  self->json = json_int_new(num);
  return self;
}
struct json *json_new_str(const char *str) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_STR;
  self->json = json_str_new(str);
  return self;
}
struct json *json_new_arr(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_ARR;
  self->json = json_arr_new();
  return self;
}
struct json *json_new_obj(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_OBJ;
  self->json = json_obj_new();
  return self;
}
void json_delete(struct json *self) {
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return;
  case JSON_TAG_INT:
    json_int_delete(self->json);
    break;
  case JSON_TAG_STR:
    json_str_delete(self->json);
    break;
  case JSON_TAG_ARR:
    json_arr_delete(self->json);
    break;
  case JSON_TAG_OBJ:
    json_obj_delete(self->json);
    break;
  default:
    break;
  }
  util_free(self);
}
bool_t json_is_null(struct json *self) {
  return json_tag(self) == JSON_TAG_NULL;
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
index_t json_count(struct json *self) {
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return 0;
  case JSON_TAG_ARR:
    return json_arr_count(json_as_arr(self));
  case JSON_TAG_OBJ:
    return json_obj_count(json_as_obj(self));
  default:
    return 1;
  }
}
struct json_str *json_as_str(struct json *self) {
  assert(json_is_str(self));
  return self->json;
}
struct json_arr *json_as_arr(struct json *self) {
  assert(json_is_arr(self));
  return self->json;
}
struct json_obj *json_as_obj(struct json *self) {
  assert(json_is_obj(self));
  return self->json;
}
void json_print(struct json *self) {
  json_printer_print(self);
}
