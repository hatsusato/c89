#include "obj.h"

#include "json.h"
#include "map.h"
#include "printer.h"
#include "printer/printer.h"
#include "util/util.h"
#include "vec.h"

struct json_obj {
  struct json_vec *vec;
};

struct json_obj *json_obj_new(void) {
  struct json_obj *self = util_malloc(sizeof(struct json_obj));
  self->vec = json_vec_new();
  return self;
}
void json_obj_delete(struct json_obj *self) {
  json_vec_delete(self->vec);
  util_free(self);
}
index_t json_obj_count(struct json_obj *self) {
  return json_vec_count(self->vec);
}
void json_obj_insert(struct json_obj *self, const char *key, struct json *val) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  if (pair) {
    json_pair_set(pair, key, val);
  } else {
    json_vec_push(self->vec, key, val);
  }
}
struct json *json_obj_get(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  return pair ? json_pair_val(pair) : json_null();
}
bool_t json_obj_has(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_vec_find(self->vec, key);
  return pair ? true : false;
}
void json_obj_foreach(struct json_obj *self, struct json_map *map) {
  json_vec_foreach(self->vec, map);
}
static void json_obj_print_map(const char *key, struct json *val, void *extra) {
  struct json_printer *printer = extra;
  if (!printer->first) {
    printer_print(printer->printer, ",");
    printer->first = false;
  }
  json_printer_newline(printer);
  printer_print(printer->printer, "\"%s\": ", key);
  json_printer_print(printer, val);
}
void json_obj_print(struct json_obj *obj, struct json_printer *printer) {
  if (0 == json_obj_count(obj)) {
    printer_print(printer->printer, "{}");
  } else {
    struct json_map map = {json_obj_print_map, NULL};
    map.extra = printer;
    printer->first = true;
    printer_print(printer->printer, "{");
    printer_indent(printer->printer, 2);
    json_obj_foreach(obj, &map);
    json_printer_newline(printer);
    printer_indent(printer->printer, -2);
    printer_print(printer->printer, "}");
  }
}
