#include "print.h"

#include "json.h"
#include "map.h"
#include "printer/printer.h"
#include "tag.h"

static void json_print_json(struct printer *self, struct json *);
static void json_print_null(struct printer *self) {
  printer_print(self, "null");
}
static void json_print_int(struct printer *self, struct json *num) {
  printer_print(self, "%d", json_int_get(num));
}
static void json_print_str(struct printer *self, struct json *str) {
  printer_quote(self, json_str_get(str));
}
static void json_print_arr_map(struct json_map *map) {
  struct printer *self = json_map_extra(map);
  if (0 < json_map_index(map)) {
    printer_print(self, ",");
  }
  printer_newline(self);
  json_print_json(self, json_map_val(map));
}
static void json_print_arr(struct printer *self, struct json *arr) {
  printer_open(self, "[");
  if (0 < json_arr_count(arr)) {
    json_arr_foreach(arr, json_print_arr_map, self);
    printer_newline(self);
  }
  printer_close(self, "]");
}
static void json_print_obj_map(struct json_map *map) {
  struct printer *self = json_map_extra(map);
  if (0 < json_map_index(map)) {
    printer_print(self, ",");
  }
  printer_newline(self);
  printer_quote(self, json_map_key(map));
  printer_print(self, ": ");
  json_print_json(self, json_map_val(map));
}
static void json_print_obj(struct printer *self, struct json *obj) {
  printer_open(self, "{");
  if (0 < json_obj_count(obj)) {
    json_obj_foreach(obj, json_print_obj_map, self);
    printer_newline(self);
  }
  printer_close(self, "}");
}
static void json_print_weak_obj_map(struct json_map *map) {
  struct printer *self = json_map_extra(map);
  const char *key = json_map_key(map);
  if (0 < json_map_index(map)) {
    printer_print(self, ", ");
  }
  printer_print(self, "%s", key);
}
static void json_print_weak(struct printer *self, struct json *weak) {
  struct json *json = json_unwrap(weak);
  printer_print(self, "(");
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    json_print_null(self);
    break;
  case JSON_TAG_INT:
    json_print_int(self, json);
    break;
  case JSON_TAG_STR:
    json_print_str(self, json);
    break;
  case JSON_TAG_ARR:
    json_print_arr(self, json);
    break;
  case JSON_TAG_OBJ:
    json_foreach(json, json_print_weak_obj_map, self);
    break;
  default:
    break;
  }
  printer_print(self, ")");
}
static void json_print_json(struct printer *self, struct json *json) {
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    json_print_null(self);
    break;
  case JSON_TAG_INT:
    json_print_int(self, json);
    break;
  case JSON_TAG_STR:
    json_print_str(self, json);
    break;
  case JSON_TAG_ARR:
    json_print_arr(self, json);
    break;
  case JSON_TAG_OBJ:
    json_print_obj(self, json);
    break;
  case JSON_TAG_WEAK:
    printer_print(self, "\"weak");
    json_print_weak(self, json);
    printer_print(self, "\"");
    break;
  default:
    break;
  }
}
void json_print_stdout(struct json *json) {
  struct printer *printer = printer_new_stdout();
  json_print_json(printer, json);
  printer_newline(printer);
  printer_del(printer);
}
void json_print_stderr(struct json *json) {
  struct printer *printer = printer_new_stderr();
  json_print_json(printer, json);
  printer_newline(printer);
  printer_del(printer);
}
