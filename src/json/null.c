#include "null.h"

#include "printer/printer.h"
#include "tag.h"
#include "type.h"
#include "util/type.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL};
  return &null;
}
void json_null_print(struct printer *printer) {
  printer_print(printer, "null");
}
