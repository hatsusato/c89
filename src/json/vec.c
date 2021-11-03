#include "vec.h"

#include <stdlib.h>

#include "map.h"
#include "null.h"
#include "pair.h"
#include "util/util.h"

struct json_pair {
  const char *key;
  struct json *val;
};

struct json_vec {
  struct json_pair *base;
  index_t count, capacity;
};

static const char *json_wrap_key(const char *key) {
  return key ? key : "";
}

static const align_t align = sizeof(struct json_pair);
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
    struct json_vec tmp;
    capacity = json_vec_capacity_ceil(capacity);
    tmp.base = util_malloc_array(align, capacity);
    tmp.count = self->count;
    tmp.capacity = capacity;
    assert(self->count <= tmp.capacity);
    util_memcpy(tmp.base, self->base, self->count, align);
    UTIL_SWAP(struct json_vec, self, &tmp);
    util_free(tmp.base);
  }
}
static int json_vec_cmp(const void *lhs, const void *rhs) {
  const struct json_pair *l = lhs, *r = rhs;
  return util_strcmp(json_pair_key(l), json_pair_key(r));
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
  json_vec_reserve(self, self->count + 1);
  json_pair_set(self->base + self->count, json_wrap_key(key), val);
  self->count++;
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
    struct json_pair pair;
    json_pair_set(&pair, json_wrap_key(key), json_null());
    return bsearch(&pair, self->base, self->count, align, json_vec_cmp);
  }
  return NULL;
}
struct json_pair *json_vec_find(struct json_vec *self, const char *key) {
  index_t i;
  struct json_pair *pair = self->base;
  for (i = 0; i < self->count; i++, pair++) {
    if (util_streq(json_wrap_key(key), json_pair_key(pair))) {
      return pair;
    }
  }
  return NULL;
}
void json_vec_foreach(struct json_vec *self, struct json_map *map) {
  index_t i;
  struct json_pair *pair = self->base;
  for (i = 0; i < self->count; i++, pair++) {
    map->index = i;
    map->key = json_pair_key(pair);
    map->val = json_pair_val(pair);
    map->map(map);
  }
}
