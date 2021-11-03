#include "vec.h"

#include "map.h"
#include "pair.h"
#include "util/util.h"

struct json_vec {
  struct json_pair *base;
  index_t count, capacity;
};

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
    tmp.base = json_pair_alloc(capacity);
    tmp.count = self->count;
    tmp.capacity = capacity;
    assert(self->count <= tmp.capacity);
    json_pair_copy(tmp.base, self->base, self->count);
    UTIL_SWAP(struct json_vec, self, &tmp);
    util_free(tmp.base);
  }
}

struct json_vec *json_vec_new(void) {
  struct json_vec *self = util_malloc(sizeof(struct json_vec));
  self->base = NULL;
  self->count = self->capacity = 0;
  return self;
}
void json_vec_delete(struct json_vec *self) {
  json_pair_free(self->base);
  util_free(self);
}
index_t json_vec_count(struct json_vec *self) {
  return self->count;
}
void json_vec_push(struct json_vec *self, const char *key, struct json *val) {
  json_vec_reserve(self, self->count + 1);
  json_pair_set(json_pair_at(self->base, self->count), key, val);
  self->count++;
}
struct json_pair *json_vec_at(struct json_vec *self, index_t index) {
  index += index < 0 ? self->count : 0;
  return (self->base && 0 <= index && index < self->count)
             ? json_pair_at(self->base, index)
             : NULL;
}
void json_vec_sort(struct json_vec *self) {
  if (self->base) {
    json_pair_sort(self->base, self->count);
  }
}
struct json_pair *json_vec_search(struct json_vec *self, const char *key) {
  return self->base ? json_pair_search(self->base, self->count, key) : NULL;
}
struct json_pair *json_vec_find(struct json_vec *self, const char *key) {
  index_t i;
  for (i = 0; i < self->count; i++) {
    struct json_pair *pair = json_pair_at(self->base, i);
    if (util_streq(key ? key : "", json_pair_key(pair))) {
      return pair;
    }
  }
  return NULL;
}
void json_vec_foreach(struct json_vec *self, struct json_map *map) {
  index_t i;
  for (i = 0; i < self->count; i++) {
    struct json_pair *pair = json_pair_at(self->base, i);
    map->index = i;
    map->key = json_pair_key(pair);
    map->val = json_pair_val(pair);
    map->map(map);
  }
}
