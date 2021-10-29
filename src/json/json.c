#include "json.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL};
  return &null;
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
  assert(pair);
  pair->val = val;
}
void json_arr_push(struct json *self, struct json *val) {
  assert(self->tag == JSON_TAG_ARR);
  json_vec_push(self->vec, NULL, val);
}
struct json *json_obj_get(struct json *self, const char *key) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  pair = json_vec_find(self->vec, key);
  return pair ? pair->val : NULL;
}
void json_obj_set(struct json *self, const char *key, struct json *val) {
  struct json_pair *pair;
  assert(self->tag == JSON_TAG_OBJ);
  pair = json_vec_find(self->vec, key);
  if (pair) {
    pair->val = val;
  } else {
    json_vec_push(self->vec, key, val);
  }
}
