#include "pair.h"

const char *json_pair_key(struct json_pair *self) {
  return self->key;
}
struct json *json_pair_val(struct json_pair *self) {
  return self->val;
}
void json_pair_set(struct json_pair *self, const char *key, struct json *val) {
  self->key = key;
  self->val = val;
}
