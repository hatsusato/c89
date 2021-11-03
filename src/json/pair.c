#include "pair.h"

struct json_pair {
  const char *key;
  struct json *val;
};

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
