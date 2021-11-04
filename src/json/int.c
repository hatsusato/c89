#include "int.h"

#include "util/util.h"

struct json_int {
  int num;
};

struct json_int *json_int_new(int num) {
  struct json_int *self = util_malloc(sizeof(struct json_int));
  self->num = num;
  return self;
}
void json_int_del(struct json_int *self) {
  util_free(self);
}
int json_int_get(struct json_int *self) {
  return self->num;
}
void json_int_set(struct json_int *self, int num) {
  self->num = num;
}
