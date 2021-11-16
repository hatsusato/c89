#include "str.h"

#include "json/new.h"
#include "util/util.h"

struct json_str {
  const char *str;
};

struct json_str *json_str_new(const char *str) {
  struct json_str *self = util_malloc(sizeof(struct json_str));
  self->str = str;
  return self;
}
void json_str_del(struct json *self) {
  util_free(json_as_str(self));
}
const char *json_str_get(struct json *self) {
  return json_as_str(self)->str;
}
void json_str_set(struct json *self, const char *str) {
  json_as_str(self)->str = str;
}
