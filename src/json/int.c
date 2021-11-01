#include "int.h"

#include "printer.h"
#include "util/util.h"

struct json_int {
  int num;
};

struct json_int *json_int_new(int num) {
  struct json_int *self = util_malloc(sizeof(struct json_int));
  self->num = num;
  return self;
}
void json_int_delete(struct json_int *self) {
  util_free(self);
}
int json_int_get(struct json_int *self) {
  return self->num;
}
void json_int_set(struct json_int *self, int num) {
  self->num = num;
}
void json_int_print(struct json_int *self, struct json_printer *printer) {
  json_printer_int(printer, self->num);
}
