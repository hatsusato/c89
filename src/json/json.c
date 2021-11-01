#include "json.h"

#include "printer.h"
#include "printer/printer.h"
#include "tag.h"
#include "type.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL};
  return &null;
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
