#include "new.h"

#include "json.h"
#include "tag.h"
#include "type.h"

struct json *json_new_int(int num) {
  return json_alloc(JSON_TAG_INT, json_int_new(num));
}
struct json *json_new_str(const char *str) {
  return json_alloc(JSON_TAG_STR, json_str_new(str));
}
struct json *json_new_arr(void) {
  return json_alloc(JSON_TAG_ARR, json_arr_new());
}
struct json *json_new_obj(void) {
  return json_alloc(JSON_TAG_OBJ, json_obj_new());
}
void json_delete(struct json *self) {
  void *data = json_data(self);
  switch (json_tag(self)) {
  case JSON_TAG_NULL:
    return;
  case JSON_TAG_INT:
    json_int_delete(data);
    break;
  case JSON_TAG_STR:
    json_str_delete(data);
    break;
  case JSON_TAG_ARR:
    json_arr_delete(data);
    break;
  case JSON_TAG_OBJ:
    json_obj_delete(data);
    break;
  default:
    break;
  }
  json_free(self);
}
