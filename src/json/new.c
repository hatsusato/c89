#include "new.h"

#include "json.h"
#include "tag.h"
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
  void *data = self->data;
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return;
  case JSON_TAG_INT:
    json_int_del(self);
    break;
  case JSON_TAG_STR:
    json_str_del(self);
    break;
  case JSON_TAG_ARR:
    json_arr_del(data);
    break;
  case JSON_TAG_OBJ:
    json_obj_del(data);
    break;
  case JSON_TAG_WEAK:
    break;
  default:
    assert(false);
    return;
  }
  util_free(self);
}

void json_del(struct json *self) {
  if (json_is_null(self)) {
    assert(0 == self->references);
  } else {
    assert(0 < self->references);
    self->references--;
    if (0 == self->references) {
      json_free(self);
    }
  }
}
void json_ref(struct json *self) {
  if (json_is_null(self)) {
    assert(0 == self->references);
  } else {
    assert(0 < self->references);
    self->references++;
  }
}
struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, 0};
  return &null;
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
struct json *json_new_weak(struct json *json) {
  return json_alloc(JSON_TAG_WEAK, json_unwrap(json));
}
bool_t json_is_null(struct json *self) {
  return json_tag(json_unwrap(self)) == JSON_TAG_NULL;
}
bool_t json_is_int(struct json *self) {
  return json_tag(json_unwrap(self)) == JSON_TAG_INT;
}
bool_t json_is_str(struct json *self) {
  return json_tag(json_unwrap(self)) == JSON_TAG_STR;
}
bool_t json_is_arr(struct json *self) {
  return json_tag(json_unwrap(self)) == JSON_TAG_ARR;
}
bool_t json_is_obj(struct json *self) {
  return json_tag(json_unwrap(self)) == JSON_TAG_OBJ;
}
bool_t json_is_weak(struct json *self) {
  return json_tag(self) == JSON_TAG_WEAK;
}
struct json_int *json_as_int(struct json *self) {
  self = json_unwrap(self);
  assert(json_is_int(self));
  return self->data;
}
struct json_str *json_as_str(struct json *self) {
  self = json_unwrap(self);
  assert(json_is_str(self));
  return self->data;
}
struct json_arr *json_as_arr(struct json *self) {
  self = json_unwrap(self);
  assert(json_is_arr(self));
  return self->data;
}
struct json_obj *json_as_obj(struct json *self) {
  self = json_unwrap(self);
  assert(json_is_obj(self));
  return self->data;
}
struct json *json_unwrap(struct json *self) {
  return json_is_weak(self) ? self->data : self;
}
