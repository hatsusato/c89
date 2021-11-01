#include "arr.h"

#include "json.h"
#include "map.h"
#include "printer.h"
#include "printer/printer.h"
#include "util/util.h"
#include "vec.h"

struct json_arr {
  struct json_vec *vec;
};

struct json_arr *json_arr_new(void) {
  struct json_arr *self = util_malloc(sizeof(struct json_arr));
  self->vec = json_vec_new();
  return self;
}
void json_arr_delete(struct json_arr *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
index_t json_arr_count(struct json_arr *self) {
  return json_vec_count(self->vec);
}
struct json *json_arr_at(struct json_arr *self, index_t index) {
  struct json_pair *pair = json_vec_at(self->vec, index);
  return pair ? json_pair_val(pair) : json_null();
}
void json_arr_push(struct json_arr *self, struct json *val) {
  json_vec_push(self->vec, NULL, val);
}
void json_arr_foreach(struct json_arr *self, struct json_map *map) {
  json_vec_foreach(self->vec, map);
}
static void json_arr_print_map(const char *key, struct json *val, void *extra) {
  struct json_printer_extra *tmp = extra;
  struct printer *printer = tmp->printer;
  bool_t *first = &tmp->first;
  if (!*first) {
    printer_print(printer, ",");
    *first = false;
  }
  printer_newline(printer);
  json_printer_print(val, printer);
  UTIL_UNUSED(key);
}
void json_arr_print(struct json_arr *self, struct printer *printer) {
  if (0 == json_arr_count(self)) {
    printer_print(printer, "[]");
  } else {
    struct json_printer_extra extra = {NULL, true};
    struct json_map map = {json_arr_print_map, NULL};
    extra.printer = printer;
    map.extra = &extra;
    printer_print(printer, "[");
    printer_indent(printer, 2);
    json_arr_foreach(self, &map);
    printer_newline(printer);
    printer_indent(printer, -2);
    printer_print(printer, "]");
  }
}
