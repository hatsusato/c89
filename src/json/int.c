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
void json_int_delete(struct json_int *self) {
  util_free(self);
}
