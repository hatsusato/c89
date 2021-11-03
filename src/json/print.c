#include "print.h"

#include "json.h"
#include "map.h"
#include "printer/printer.h"
#include "type.h"

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
static void json_print_map(struct json_map *map) {
  struct printer *self = map->extra;
  if (0 < map->index) {
    printer_print(self, ",");
  }
  printer_newline(self);
  if (map->is_obj) {
    printer_print(self, "\"%s\": ", map->key);
  }
  json_print_recurse(self, map->val);
}
static void json_print_arr(struct printer *self, struct json_arr *arr) {
  printer_print(self, "[");
  printer_indent(self, 2);
  if (0 < json_arr_count(arr)) {
    struct json_map map;
    map.map = json_print_map;
    map.extra = self;
    json_arr_foreach(arr, &map);
    printer_newline(self);
  }
  printer_indent(self, -2);
  printer_print(self, "]");
}
static void json_print_obj(struct printer *self, struct json_obj *obj) {
  printer_print(self, "{");
  printer_indent(self, 2);
  if (0 < json_obj_count(obj)) {
    struct json_map map;
    map.map = json_print_map;
    map.extra = self;
    json_obj_foreach(obj, &map);
    printer_newline(self);
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
  default:
    break;
  }
}
void json_print_stdout(struct json *json) {
  struct printer *printer = printer_new_stdout();
  json_print_recurse(printer, json);
  printer_newline(printer);
  printer_delete(printer);
}
