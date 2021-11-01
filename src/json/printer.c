#include "printer.h"

#include "json.h"
#include "printer/printer.h"
#include "tag.h"
#include "util/util.h"

static void json_printer_obj_map(const char *key, struct json *val,
                                 void *extra) {
  struct json_printer_extra *tmp = extra;
  struct printer *printer = tmp->printer;
  bool_t *first = &tmp->first;
  if (!*first) {
    printer_print(printer, ",");
    *first = false;
  }
  printer_newline(printer);
  printer_print(printer, "\"%s\": ", key);
  json_printer_print(val, printer);
}
static void json_printer_obj(struct json_obj *obj, struct printer *printer) {
  if (0 == json_obj_count(obj)) {
    printer_print(printer, "{}");
  } else {
    struct json_printer_extra extra = {NULL, true};
    struct json_map map = {json_printer_obj_map, NULL};
    extra.printer = printer;
    map.extra = &extra;
    printer_print(printer, "{");
    printer_indent(printer, 2);
    json_obj_foreach(obj, &map);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "}");
  }
}

void json_printer_print(struct json *json, struct printer *printer) {
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    printer_print(printer, "null");
    break;
  case JSON_TAG_STR:
    json_str_print(json_as_str(json), printer);
    break;
  case JSON_TAG_ARR:
    json_arr_print(json_as_arr(json), printer);
    break;
  case JSON_TAG_OBJ:
    json_printer_obj(json_as_obj(json), printer);
    break;
  default:
    break;
  }
}
