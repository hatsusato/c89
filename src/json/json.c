#include "json.h"

#include "printer.h"
#include "printer/printer.h"
#include "tag.h"
#include "type.h"
#include "util/util.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL};
  return &null;
}
struct json *json_new_str(const char *str) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_STR;
  self->str = json_str_new(str);
  self->arr = NULL;
  self->obj = NULL;
  return self;
}
struct json *json_new_arr(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_ARR;
  self->str = NULL;
  self->arr = json_arr_new();
  self->obj = NULL;
  return self;
}
struct json *json_new_obj(void) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = JSON_TAG_OBJ;
  self->str = NULL;
  self->arr = NULL;
  self->obj = json_obj_new();
  return self;
}
void json_delete(struct json *self) {
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return;
  case JSON_TAG_STR:
    json_str_delete(self->str);
    break;
  case JSON_TAG_ARR:
    json_arr_delete(self->arr);
    break;
  case JSON_TAG_OBJ:
    json_obj_delete(self->obj);
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
  return json_is_str(self) ? self->str : NULL;
}
struct json_arr *json_as_arr(struct json *self) {
  return json_is_arr(self) ? self->arr : NULL;
}
struct json_obj *json_as_obj(struct json *self) {
  return json_is_obj(self) ? self->obj : NULL;
}
void json_print(struct json *self) {
  struct printer *printer = printer_new_stdout();
  json_printer_print(self, printer);
  printer_newline(printer);
  printer_delete(printer);
}
