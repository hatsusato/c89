#include "str.h"

#include "printer/printer.h"
#include "util/util.h"

struct json_str {
  const char *str;
};

struct json_str *json_str_new(const char *str) {
  struct json_str *self = util_malloc(sizeof(struct json_str));
  self->str = str;
  return self;
}
void json_str_delete(struct json_str *self) {
  util_free(self);
}
const char *json_str_get(struct json_str *self) {
  return self->str;
}
void json_str_set(struct json_str *self, const char *str) {
  self->str = str;
}
void json_str_print(struct json_str *self, struct printer *printer) {
  printer_print(printer, "\"%s\"", json_str_get(self));
}
