#include "printer.h"

#include "json.h"
#include "printer/printer.h"
#include "tag.h"

void json_printer_print(struct json_printer *self, struct json *json) {
  switch (json_tag(json)) {
  case JSON_TAG_NULL:
    json_null_print(self);
    break;
  case JSON_TAG_STR:
    json_str_print(json_as_str(json), self);
    break;
  case JSON_TAG_ARR:
    json_arr_print(json_as_arr(json), self);
    break;
  case JSON_TAG_OBJ:
    json_obj_print(json_as_obj(json), self);
    break;
  default:
    break;
  }
}
void json_printer_newline(struct json_printer *self) {
  printer_newline(self->printer);
}
void json_printer_open(struct json_printer *self, const char *punct) {
  printer_print(self->printer, "%s", punct);
  printer_indent(self->printer, 2);
}
void json_printer_close(struct json_printer *self, const char *punct) {
  printer_indent(self->printer, -2);
  printer_print(self->printer, "%s", punct);
}
void json_printer_comma(struct json_printer *self) {
  if (!self->first) {
    printer_print(self->printer, ",");
  }
  self->first = false;
}
void json_printer_symbol(struct json_printer *self, const char *symbol) {
  printer_print(self->printer, "\"%s\"", symbol);
}
void json_printer_str(struct json_printer *self, const char *str) {
  printer_print(self->printer, "%s", str);
}
