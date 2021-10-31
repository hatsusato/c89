#include "printer.h"

#include "json.h"
#include "printer/printer.h"
#include "str.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

static void json_printer_null(struct json *json, struct printer *printer) {
  UTIL_UNUSED(json);
  assert(json->tag == JSON_TAG_NULL);
  printer_print(printer, "null");
}
static void json_printer_str(struct json *json, struct printer *printer) {
  struct json_str *str = json_as_str(json);
  assert(str);
  printer_print(printer, "\"%s\"", json_str_get(str));
}
static void json_printer_arr_map(struct json_map *map) {
  struct printer *printer = map->extra;
  if (0 < map->index) {
    printer_print(printer, ",");
  }
  printer_newline(printer);
  json_printer_print(map->val, printer);
}
static void json_printer_arr(struct json *json, struct printer *printer) {
  assert(json->tag == JSON_TAG_ARR);
  if (0 == json_count(json)) {
    printer_print(printer, "[]");
  } else {
    printer_print(printer, "[");
    printer_indent(printer, 2);
    json_vec_map(json->vec, json_printer_arr_map, printer);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "]");
  }
}
static void json_printer_obj_map(struct json_map *map) {
  struct printer *printer = map->extra;
  if (0 < map->index) {
    printer_print(printer, ",");
  }
  printer_newline(printer);
  printer_print(printer, "\"%s\": ", map->key);
  json_printer_print(map->val, printer);
}
static void json_printer_obj(struct json *json, struct printer *printer) {
  assert(json->tag == JSON_TAG_OBJ);
  if (0 == json_count(json)) {
    printer_print(printer, "{}");
  } else {
    printer_print(printer, "{");
    printer_indent(printer, 2);
    json_vec_map(json->vec, json_printer_obj_map, printer);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "}");
  }
}

void json_printer_print(struct json *json, struct printer *printer) {
  switch (json->tag) {
  case JSON_TAG_NULL:
    json_printer_null(json, printer);
    break;
  case JSON_TAG_STR:
    json_printer_str(json, printer);
    break;
  case JSON_TAG_ARR:
    json_printer_arr(json, printer);
    break;
  case JSON_TAG_OBJ:
    json_printer_obj(json, printer);
    break;
  default:
    break;
  }
}
