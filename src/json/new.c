#include "new.h"

#include "json.h"
#include "type.h"
#include "util/util.h"

static struct json *json_alloc(enum json_tag tag, void *data) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = tag;
  self->data = data;
  self->references = 1;
  return self;
}
static void json_free(struct json *self) {
  void *data = json_data(self);
  switch (json_tag(self)) {
  case JSON_TAG_INT:
    json_int_del(data);
    break;
  case JSON_TAG_STR:
    json_str_del(data);
    break;
  case JSON_TAG_ARR:
    json_arr_del(data);
    break;
  case JSON_TAG_OBJ:
    json_obj_del(data);
    break;
  default:
    assert(false);
    return;
  }
  util_free(self);
}

struct json *json_new_int(int num) {
  return json_alloc(JSON_TAG_INT, json_int_new(num));
}
struct json *json_new_str(const char *str) {
  return json_alloc(JSON_TAG_STR, json_str_new(str));
}
struct json *json_new_arr(void) {
  return json_alloc(JSON_TAG_ARR, json_arr_new());
}
struct json *json_new_obj(void) {
  return json_alloc(JSON_TAG_OBJ, json_obj_new());
}
void json_del(struct json *self) {
  if (json_is_null(self)) {
    assert(0 == self->references);
  } else {
    self->references--;
    assert(0 <= self->references);
    if (0 == self->references) {
      json_free(self);
    }
  }
}
