#include "printer.h"

#include "json.h"
#include "map.h"
#include "printer/printer.h"
#include "type.h"
#include "util/util.h"

static void json_printer_str(struct json_str *str, struct printer *printer) {
  printer_print(printer, "\"%s\"", json_str_get(str));
}
static void json_printer_arr_map(struct json *json,
                                 struct json_map_extra *extra) {
  struct printer *printer = extra->extra;
  if (0 < extra->index) {
    printer_print(printer, ",");
  }
  printer_newline(printer);
  json_printer_print(json, printer);
}
static void json_printer_arr(struct json_arr *arr, struct printer *printer) {
  if (0 == json_arr_count(arr)) {
    printer_print(printer, "[]");
  } else {
    struct json_map map = {json_printer_arr_map, NULL};
    map.extra = printer;
    printer_print(printer, "[");
    printer_indent(printer, 2);
    json_arr_foreach(arr, &map);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "]");
  }
}
static void json_printer_obj_map(struct json *json,
                                 struct json_map_extra *extra) {
  struct printer *printer = extra->extra;
  if (0 < extra->index) {
    printer_print(printer, ",");
  }
  printer_newline(printer);
  printer_print(printer, "\"%s\": ", extra->key);
  json_printer_print(json, printer);
}
static void json_printer_obj(struct json_obj *obj, struct printer *printer) {
  if (0 == json_obj_count(obj)) {
    printer_print(printer, "{}");
  } else {
    struct json_map map = {json_printer_obj_map, NULL};
    map.extra = printer;
    printer_print(printer, "{");
    printer_indent(printer, 2);
    json_obj_foreach(obj, &map);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "}");
  }
}

void json_printer_print(struct json *json, struct printer *printer) {
  switch (json->tag) {
  case JSON_TAG_NULL:
    printer_print(printer, "null");
    break;
  case JSON_TAG_STR:
    json_printer_str(json_as_str(json), printer);
    break;
  case JSON_TAG_ARR:
    json_printer_arr(json_as_arr(json), printer);
    break;
  case JSON_TAG_OBJ:
    json_printer_obj(json_as_obj(json), printer);
    break;
  default:
    break;
  }
}
