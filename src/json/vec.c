#include "vec.h"

#include <stdlib.h>

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
  util_memcpy(self->base + self->count, base, count, align);
  self->count += count;
}
static void json_vec_resize(struct json_vec *self, index_t capacity) {
  struct json_vec tmp = {NULL, 0, 0};
  assert(self->count < capacity);
  tmp.base = util_malloc_array(align, capacity);
  json_vec_insert(&tmp, self->base, self->count);
  UTIL_SWAP(struct json_vec, self, &tmp);
  util_free(tmp.base);
}
static int json_vec_cmp(const void *lhs, const void *rhs) {
  const struct json_pair *l = lhs, *r = rhs;
  return util_strcmp(l->key, r->key);
}

struct json_vec *json_vec_new(void) {
  struct json_vec *self = util_malloc(sizeof(struct json_vec));
  self->base = NULL;
  self->count = self->capacity = 0;
  return self;
}
void json_vec_delete(struct json_vec *self) {
  util_free(self->base);
  util_free(self);
}
index_t json_vec_count(struct json_vec *self) {
  return self->count;
}
void json_vec_push(struct json_vec *self, const char *key, struct json *val) {
  struct json_pair pair;
  index_t capacity = self->count + 1;
  if (self->capacity < capacity) {
    self->capacity = json_vec_capacity_ceil(capacity);
    json_vec_resize(self, self->capacity);
  }
  pair.key = key;
  pair.val = val;
  json_vec_insert(self, &pair, 1);
}
struct json_pair *json_vec_at(struct json_vec *self, index_t index) {
  index += index < 0 ? self->count : 0;
  return (0 <= index && index < self->count) ? self->base + index : NULL;
}
void json_vec_sort(struct json_vec *self) {
  if (self->base) {
    qsort(self->base, self->count, align, json_vec_cmp);
  }
}
struct json_pair *json_vec_search(struct json_vec *self, const char *key) {
  if (self->base) {
    struct json_pair pair = {NULL, NULL};
    pair.key = key;
    return bsearch(&pair, self->base, self->count, align, json_vec_cmp);
  }
  return NULL;
}
struct json_pair *json_vec_find(struct json_vec *self, const char *key) {
  index_t i;
  for (i = 0; i < self->count; i++) {
    struct json_pair *pair = self->base + i;
    if (util_streq(key, pair->key)) {
      return pair;
    }
  }
  return NULL;
}
void json_vec_map(struct json_vec *self, json_map_t map) {
  index_t i;
  for (i = 0; i < self->count; i++) {
    map(self->base + i);
  }
}
