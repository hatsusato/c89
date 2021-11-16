#include "unittest.h"

#include "json.h"
#include "util/util.h"

void json_arr_unittest(void) {
  struct json *json = json_new_arr();
  struct json_arr *arr = json_as_arr(json);
  index_t i, count = 100;
  char(*str)[2] = util_malloc_array(count, sizeof(char[2]));
  for (i = 0; i < count; i++) {
    str[i][0] = 'a' + (i * 100) % 26;
    str[i][1] = 0;
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_new_str(str[i]);
    json_arr_push(arr, val);
    json_del(val);
  }
  for (i = 0; i < count; i++) {
    struct json *elem = json_arr_at(arr, i);
    assert(util_streq(json_str_get(elem), str[i]));
    UTIL_UNUSED(elem);
  }
  util_free(str);
  json_del(json);
}

void json_obj_unittest(void) {
  struct json *json = json_new_obj();
  struct json_obj *obj = json_as_obj(json);
  index_t i, count = 100;
  char(*key)[2] = util_malloc_array(count, sizeof(char[2]));
  for (i = 0; i < count; i++) {
    key[i][0] = 'a' + (i * 100) % 26;
    key[i][1] = 0;
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_new_str(key[i]);
    json_obj_insert(obj, key[i], val);
    json_del(val);
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_obj_get(obj, key[i]);
    assert(util_streq(json_str_get(val), key[i]));
    UTIL_UNUSED(val);
  }
  assert(!json_obj_has(obj, "0"));
  util_free(key);
  json_del(json);
}

void json_unittest(void) {
  json_arr_unittest();
  json_obj_unittest();
}
