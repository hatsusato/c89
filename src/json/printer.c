#include "printer.h"

#include "json.h"
#include "printer/printer.h"
#include "type.h"
#include "util/util.h"

static void json_printer_null(struct json *json, struct printer *printer) {
  UTIL_UNUSED(json);
  assert(json->tag == JSON_TAG_NULL);
  printer_print(printer, "null");
}
static void json_printer_str(struct json *json, struct printer *printer) {
  assert(json->tag == JSON_TAG_STR);
  printer_print(printer, "\"%s\"", json_str_get(json));
}
static void json_printer_arr(struct json *json, struct printer *printer) {
  index_t i, count;
  assert(json->tag == JSON_TAG_ARR);
  count = json_count(json);
  printer_print(printer, "[");
  if (0 < count) {
    printer_indent(printer, 2);
    printer_newline(printer);
    json_printer_print(json_arr_get(json, 0), printer);
    for (i = 1; i < count; i++) {
      printer_print(printer, ",");
      printer_newline(printer);
      json_printer_print(json_arr_get(json, i), printer);
    }
    printer_indent(printer, -2);
    printer_newline(printer);
  }
  printer_print(printer, "]");
}
static void json_printer_obj(struct json *json, struct printer *printer) {
  index_t i, count;
  assert(json->tag == JSON_TAG_OBJ);
  count = json_count(json);
  printer_print(printer, "{");
  if (0 < count) {
    printer_indent(printer, 2);
    printer_newline(printer);
    printer_print(printer, "\"%s\": ", json_obj_key(json, 0));
    json_printer_print(json_obj_val(json, 0), printer);
    for (i = 1; i < count; i++) {
      printer_print(printer, ",");
      printer_newline(printer);
      printer_print(printer, "\"%s\": ", json_obj_key(json, i));
      json_printer_print(json_obj_val(json, i), printer);
    }
    printer_indent(printer, -2);
    printer_newline(printer);
  }
  printer_print(printer, "}");
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
void json_print(struct json *json, struct printer *printer) {
  json_printer_print(json, printer);
  printer_newline(printer);
}
