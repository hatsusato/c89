#include "print.h"

#include "closure.h"
#include "json.h"
#include "printer/printer.h"
#include "type.h"
#include "util/util.h"

void json_print_recurse(struct printer *self, struct json *);

static void json_print_null(struct printer *self) {
  printer_print(self, "null");
}
static void json_print_int(struct printer *self, struct json_int *num) {
  printer_print(self, "%d", json_int_get(num));
}
static void json_print_str(struct printer *self, struct json_str *str) {
  printer_print(self, "\"%s\"", json_str_get(str));
}
static void json_print_arr_map(struct json *args) {
  struct json *printer = json_get(args, "printer");
  struct json *index = json_get(args, "index");
  struct json *val = json_get(args, "val");
  struct printer *self = json_get_any(printer);
  assert(json_is_int(index));
  if (0 < json_int_get(json_as_int(index))) {
    printer_print(self, ",");
  }
  printer_newline(self);
  json_print_recurse(self, val);
}
static void json_print_arr(struct printer *self, struct json_arr *arr) {
  printer_print(self, "[");
  printer_indent(self, 2);
  if (0 < json_arr_count(arr)) {
    struct json_closure *map = json_closure_new(json_print_arr_map);
    struct json *printer = json_new_any(self);
    struct json *index = json_new_int(0);
    json_closure_insert(map, "printer", printer);
    json_closure_insert(map, "index", index);
    json_arr_map(arr, map);
    printer_newline(self);
    json_delete(index);
    json_delete(printer);
    json_closure_delete(map);
  }
  printer_indent(self, -2);
  printer_print(self, "]");
}
static void json_print_obj_map(struct json *args) {
  struct json *printer = json_get(args, "printer");
  struct json *index = json_get(args, "index");
  struct json *key = json_get(args, "key");
  struct json *val = json_get(args, "val");
  struct printer *self = json_get_any(printer);
  assert(json_is_int(index));
  if (0 < json_int_get(json_as_int(index))) {
    printer_print(self, ",");
  }
  printer_newline(self);
  printer_print(self, "\"%s\": ", json_get_str(key));
  json_print_recurse(self, val);
}
static void json_print_obj(struct printer *self, struct json_obj *obj) {
  printer_print(self, "{");
  printer_indent(self, 2);
  if (0 < json_obj_count(obj)) {
    struct json_closure *map = json_closure_new(json_print_obj_map);
    struct json *printer = json_new_any(self);
    struct json *index = json_new_int(0);
    struct json *key = json_new_str("");
    json_closure_insert(map, "printer", printer);
    json_closure_insert(map, "index", index);
    json_closure_insert(map, "key", key);
    json_obj_map(obj, map);
    printer_newline(self);
    json_delete(key);
    json_delete(index);
    json_delete(printer);
    json_closure_delete(map);
  }
  printer_indent(self, -2);
  printer_print(self, "}");
}
void json_print_recurse(struct printer *self, struct json *json) {
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    json_print_null(self);
    break;
  case JSON_TAG_INT:
    json_print_int(self, json_as_int(json));
    break;
  case JSON_TAG_STR:
    json_print_str(self, json_as_str(json));
    break;
  case JSON_TAG_ARR:
    json_print_arr(self, json_as_arr(json));
    break;
  case JSON_TAG_OBJ:
    json_print_obj(self, json_as_obj(json));
    break;
  case JSON_TAG_ANY:
    printer_print(self, "<any>");
    break;
  default:
    break;
  }
}
void json_print_print(struct json *json) {
  struct printer *printer = printer_new_stdout();
  json_print_recurse(printer, json);
  printer_newline(printer);
  printer_delete(printer);
}
