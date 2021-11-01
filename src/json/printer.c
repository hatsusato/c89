#include "printer.h"

#include "json.h"
#include "tag.h"

void json_printer_print(struct json *json, struct printer *printer) {
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    json_null_print(printer);
    break;
  case JSON_TAG_STR:
    json_str_print(json_as_str(json), printer);
    break;
  case JSON_TAG_ARR:
    json_arr_print(json_as_arr(json), printer);
    break;
  case JSON_TAG_OBJ:
    json_obj_print(json_as_obj(json), printer);
    break;
  default:
    break;
  }
}
