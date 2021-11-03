#include "arr.h"

#include "map.h"
#include "null.h"
#include "printer.h"
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
  map->is_obj = false;
  json_vec_foreach(self->vec, map);
}
void json_arr_map(struct json_arr *self, struct json_closure *map) {
  json_vec_map(self->vec, map);
}
static void json_arr_print_map(struct json_map *map) {
  struct json_printer *printer = map->extra;
  json_printer_comma(printer);
  json_printer_newline(printer);
  json_printer_recurse(printer, map->val);
}
void json_arr_print(struct json_arr *self, struct json_printer *printer) {
  json_printer_open(printer, "[");
  if (0 < json_arr_count(self)) {
    struct json_map map;
    map.map = json_arr_print_map;
    map.extra = printer;
    json_printer_init(printer);
    json_arr_foreach(self, &map);
    json_printer_newline(printer);
  }
  json_printer_close(printer, "]");
}
