#include "pair.h"

#include <stdlib.h>

#include "new.h"
#include "util/util.h"

struct json_pair {
  const char *key;
  struct json *val;
};

static int json_pair_cmp(const void *lhs, const void *rhs) {
  const struct json_pair *l = lhs, *r = rhs;
  return util_strcmp(l->key, r->key);
}
static const align_t align = sizeof(struct json_pair);

struct json_pair *json_pair_alloc(index_t count) {
  struct json_pair *self = util_malloc_array(count, align);
  return self;
}
void json_pair_free(struct json_pair *self) {
  util_free(self);
}
void json_pair_copy(struct json_pair *self, const struct json_pair *other,
                    index_t count) {
  util_memcpy(self, other, count, align);
}
const char *json_pair_key(const struct json_pair *self) {
  return self->key;
}
struct json *json_pair_val(const struct json_pair *self) {
  return self->val;
}
void json_pair_set(struct json_pair *self, const char *key, struct json *val) {
  self->key = key;
  self->val = val;
}
struct json_pair *json_pair_at(struct json_pair *self, index_t index) {
  return self + index;
}
void json_pair_sort(struct json_pair *self, index_t count) {
  qsort(self, count, align, json_pair_cmp);
}
struct json_pair *json_pair_search(struct json_pair *self, index_t count,
                                   const char *key) {
  struct json_pair pair;
  json_pair_set(&pair, key, json_null());
  return bsearch(&pair, self, count, align, json_pair_cmp);
}
