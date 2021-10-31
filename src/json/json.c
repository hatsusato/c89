#include "json.h"

#include <stdio.h>

#include "printer.h"
#include "printer/printer.h"
#include "str.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL, NULL};
  return &null;
}
bool_t json_is_null(struct json *self) {
  return self->tag == JSON_TAG_NULL;
}
bool_t json_is_str(struct json *self) {
  return self->tag == JSON_TAG_STR;
}
bool_t json_is_arr(struct json *self) {
  return self->tag == JSON_TAG_ARR;
}
bool_t json_is_obj(struct json *self) {
  return self->tag == JSON_TAG_OBJ;
}
index_t json_count(struct json *self) {
  switch (self->tag) {
  case JSON_TAG_NULL:
    return 0;
  case JSON_TAG_ARR:
    /* FALLTHROUGH */
  case JSON_TAG_OBJ:
    return json_vec_count(self->vec);
  default:
    return 1;
  }
}
struct json_str *json_as_str(struct json *self) {
  return self->tag == JSON_TAG_STR ? self->str : NULL;
}
struct json_arr *json_as_arr(struct json *self) {
  return self->tag == JSON_TAG_ARR ? self->arr : NULL;
}
struct json *json_json_obj_get(struct json *self, const char *key) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  assert(key);
  pair = json_vec_find(self->vec, key);
  return pair ? pair->val : NULL;
}
void json_json_obj_set(struct json *self, const char *key, struct json *val) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  assert(key && val);
  pair = json_vec_find(self->vec, key);
  if (pair) {
    pair->val = val;
  } else {
    json_vec_push(self->vec, key, val);
  }
}
void json_print(struct json *self) {
  struct printer *printer = printer_new(stdout);
  json_printer_print(self, printer);
  printer_newline(printer);
  printer_delete(printer);
}
