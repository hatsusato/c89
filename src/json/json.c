#include "json.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL};
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
const char *json_str_get(struct json *self) {
  assert(self->tag == JSON_TAG_STR);
  return self->str;
}
struct json *json_arr_get(struct json *self, index_t key) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_ARR);
  pair = json_vec_at(self->vec, key);
  return pair ? pair->val : NULL;
}
void json_arr_set(struct json *self, index_t key, struct json *val) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_ARR);
  pair = json_vec_at(self->vec, key);
  assert(pair && val);
  pair->val = val;
}
void json_arr_push(struct json *self, struct json *val) {
  assert(self->tag == JSON_TAG_ARR);
  assert(val);
  json_vec_push(self->vec, NULL, val);
}
struct json *json_obj_get(struct json *self, const char *key) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  assert(key);
  pair = json_vec_find(self->vec, key);
  return pair ? pair->val : NULL;
}
void json_obj_set(struct json *self, const char *key, struct json *val) {
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
const char *json_obj_key(struct json *self, index_t index) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  pair = json_vec_at(self->vec, index);
  assert(pair);
  return pair->key;
}
struct json *json_obj_val(struct json *self, index_t index) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  pair = json_vec_at(self->vec, index);
  assert(pair);
  return pair->val;
}
