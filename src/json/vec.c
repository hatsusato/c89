#include "vec.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "type.h"
#include "util/util.h"

static const align_t align = sizeof(struct json_pair);
static index_t json_vec_capacity_ceil(index_t capacity) {
  enum { initial_capacity = 8 };
  index_t ceil = initial_capacity;
  while (ceil < capacity) {
    ceil *= 2;
  }
  return ceil;
}
static void json_vec_insert(struct json_vec *self, struct json_pair *base,
                            index_t count) {
  if (0 < count) {
    assert(self->array.base && base);
    memcpy(self->array.base + align * self->array.count, base, align * count);
    self->array.count += count;
  }
}
static void json_vec_resize(struct json_vec *self, index_t capacity) {
  struct json_vec tmp = {{NULL, 0}, 0};
  assert(self->array.count < capacity);
  tmp.array.base = util_malloc_array(align, capacity);
  json_vec_insert(&tmp, self->array.base, self->array.count);
  UTIL_SWAP(struct json_vec, self, &tmp);
  util_free(self->array.base);
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
  index_t capacity = self->array.count + 1;
  if (self->capacity < capacity) {
    self->capacity = json_vec_capacity_ceil(capacity);
    json_vec_resize(self, self->capacity);
  }
  pair.key = key;
  pair.val = val;
  json_vec_insert(self, &pair, 1);
}
void json_vec_sort(struct json_vec *self, cmp_t cmp) {
  if (self->array.base) {
    qsort(self->array.base, self->array.count, align, cmp);
  }
}
struct json_pair *json_vec_search(struct json_vec *self, struct json_pair *key,
                                  cmp_t cmp) {
  if (self->array.base) {
    return bsearch(key, self->array.base, self->array.count, align, cmp);
  }
  return NULL;
}
