#include "int.h"

#include "json/new.h"
#include "util/util.h"

struct json_int {
  int num;
};

struct json_int *json_int_new(int num) {
  struct json_int *self = util_malloc(sizeof(struct json_int));
  self->num = num;
  return self;
}
void json_int_del(struct json *self) {
  util_free(json_as_int(self));
}
int json_int_get(struct json *self) {
  return json_as_int(self)->num;
}
void json_int_set(struct json *self, int num) {
  json_as_int(self)->num = num;
}
