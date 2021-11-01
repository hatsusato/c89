#include "null.h"

#include "printer.h"
#include "tag.h"
#include "type.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL, NULL};
  return &null;
}
void json_null_print(struct json_printer *printer) {
  json_printer_str(printer, "null");
}
