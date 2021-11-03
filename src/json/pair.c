#include "pair.h"

#include <stdlib.h>

#include "null.h"
#include "util/util.h"

struct json_pair {
  const char *key;
  struct json *val;
};

static int json_pair_cmp(const void *lhs, const void *rhs) {
  const struct json_pair *l = lhs, *r = rhs;
  return util_strcmp(l->key, r->key);
}

const char *json_pair_key(const struct json_pair *self) {
  return self->key;
}
struct json *json_pair_val(const struct json_pair *self) {
  return self->val;
}
void json_pair_set(struct json_pair *self, const char *key, struct json *val) {
  self->key = key ? key : "";
  self->val = val;
}
struct json_pair *json_pair_search(struct json_pair *self, index_t count,
                                   const char *key) {
  struct json_pair pair;
  json_pair_set(&pair, key, json_null());
  return bsearch(&pair, self, count, sizeof(struct json_pair), json_pair_cmp);
}
