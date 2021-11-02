#include "obj.h"

#include "map.h"
#include "null.h"
#include "printer.h"
#include "util/util.h"
#include "vec.h"

struct json_obj {
  struct json_vec *vec;
  bool_t sorted;
};

struct json_obj *json_obj_new(void) {
  struct json_obj *self = util_malloc(sizeof(struct json_obj));
  self->vec = json_vec_new();
  self->sorted = false;
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
  struct json_pair *pair = json_obj_find(self, key);
  if (pair) {
    json_pair_set(pair, key, val);
  } else {
    json_vec_push(self->vec, key, val);
    if (self->sorted) {
      json_vec_sort(self->vec);
    }
  }
}
struct json *json_obj_get(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_obj_find(self, key);
  return pair ? json_pair_val(pair) : json_null();
}
bool_t json_obj_has(struct json_obj *self, const char *key) {
  struct json_pair *pair = json_obj_find(self, key);
  return UTIL_BOOL(pair);
}
struct json_pair *json_obj_find(struct json_obj *self, const char *key) {
  if (self->sorted) {
    return json_vec_search(self->vec, key);
  } else {
    return json_vec_find(self->vec, key);
  }
}
void json_obj_sort(struct json_obj *self) {
  self->sorted = true;
  json_vec_sort(self->vec);
}
void json_obj_foreach(struct json_obj *self, struct json_map *map) {
  json_vec_foreach(self->vec, map);
}
static void json_obj_print_map(const char *key, struct json *val, void *extra) {
  struct json_printer *printer = extra;
  json_printer_comma(printer);
  json_printer_newline(printer);
  json_printer_symbol(printer, key);
  json_printer_str(printer, ": ");
  json_printer_recurse(printer, val);
}
void json_obj_print(struct json_obj *obj, struct json_printer *printer) {
  json_printer_open(printer, "{");
  if (0 < json_obj_count(obj)) {
    struct json_map map = {json_obj_print_map, NULL};
    map.extra = printer;
    json_printer_init(printer);
    json_obj_foreach(obj, &map);
    json_printer_newline(printer);
  }
  json_printer_close(printer, "}");
}
