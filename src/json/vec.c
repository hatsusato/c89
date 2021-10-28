#include "vec.h"

#include "array.h"
#include "type.h"
#include "util/util.h"

static index_t json_vec_capacity_ceil(index_t capacity) {
  enum { initial_capacity = 8 };
  index_t ceil = initial_capacity;
  while (ceil < capacity) {
    ceil *= 2;
  }
  return ceil;
}
static void json_vec_reserve(struct json_vec *self, index_t capacity) {
  if (self->capacity < capacity) {
    self->capacity = json_vec_capacity_ceil(capacity);
    json_array_resize(&self->array, self->capacity);
  }
}

struct json_vec *json_vec_new(void) {
  struct json_vec *self = util_malloc(sizeof(struct json_vec));
  self->array.base = NULL;
  self->array.count = self->capacity = 0;
  return self;
}
void json_vec_delete(struct json_vec *self) {
  util_free(self->array.base);
  util_free(self);
}
void json_vec_push(struct json_vec *self, const char *key, struct json *val) {
  struct json_pair pair;
  pair.key = key;
  pair.val = val;
  json_vec_reserve(self, self->array.count + 1);
  json_array_insert(&self->array, &pair, 1);
}
