#include "printer.h"

#include "json.h"
#include "printer/printer.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

static void json_print_rec(struct json *json, struct printer *printer);
static void json_print_null(struct json *json, struct printer *printer) {
  UTIL_UNUSED(json);
  assert(json->tag == JSON_TAG_NULL);
  printer_print(printer, "null");
}
static void json_print_str(struct json *json, struct printer *printer) {
  assert(json->tag == JSON_TAG_STR);
  printer_print(printer, "\"%s\"", json_str_get(json));
}
static void json_print_arr(struct json *json, struct printer *printer) {
  index_t i, count;
  assert(json->tag == JSON_TAG_ARR);
  count = json_count(json);
  printer_print(printer, "[");
  if (0 < count) {
    printer_indent(printer, 2);
    printer_newline(printer);
    json_print_rec(json_arr_get(json, 0), printer);
    for (i = 1; i < count; i++) {
      printer_print(printer, ",");
      printer_newline(printer);
      json_print_rec(json_arr_get(json, i), printer);
    }
    printer_indent(printer, -2);
    printer_newline(printer);
  }
  printer_print(printer, "]");
}
static void json_print_pair(struct json_pair *pair, struct printer *printer) {
  printer_print(printer, "\"%s\": ", pair->key);
  json_print(pair->val, printer);
}
static void json_print_obj(struct json *json, struct printer *printer) {
  index_t i, count;
  assert(json->tag == JSON_TAG_OBJ);
  count = json_count(json);
  printer_print(printer, "{");
  if (0 < count) {
    printer_indent(printer, 2);
    printer_newline(printer);
    json_print_pair(json_vec_at(json->vec, 0), printer);
    for (i = 1; i < count; i++) {
      printer_print(printer, ",");
      printer_newline(printer);
      json_print_pair(json_vec_at(json->vec, i), printer);
    }
    printer_indent(printer, -2);
    printer_newline(printer);
  }
  printer_print(printer, "}");
}
static void json_print_rec(struct json *json, struct printer *printer) {
  switch (json->tag) {
  case JSON_TAG_NULL:
    json_print_null(json, printer);
    break;
  case JSON_TAG_STR:
    json_print_str(json, printer);
    break;
  case JSON_TAG_ARR:
    json_print_arr(json, printer);
    break;
  case JSON_TAG_OBJ:
    json_print_obj(json, printer);
    break;
  default:
    break;
  }
}

void json_print(struct json *json, struct printer *printer) {
  json_print_rec(json, printer);
  printer_newline(printer);
}
