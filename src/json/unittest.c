#include "unittest.h"

#include "factory.h"
#include "json.h"
#include "str.h"
#include "util/util.h"

void json_arr_unittest(void) {
  struct json_factory *factory = json_factory_new();
  struct json *arr = json_factory_arr(factory);
  index_t i, count = 100;
  char(*str)[2] = util_malloc_array(sizeof(char[2]), count);
  for (i = 0; i < count; i++) {
    str[i][0] = 'a' + (i * 100) % 26;
    str[i][1] = 0;
  }
  assert(!json_json_arr_get(arr, 0));
  for (i = 0; i < count; i++) {
    struct json *val = json_factory_arr(factory);
    json_json_arr_push(arr, val);
  }
  for (i = 0; i < count; i++) {
    assert(json_json_arr_get(arr, i));
    json_json_arr_set(arr, i, json_factory_str(factory, str[i]));
  }
  for (i = 0; i < count; i++) {
    struct json *elem = json_json_arr_get(arr, i);
    struct json_str *jstr = json_as_str(elem);
    assert(jstr);
    assert(util_streq(json_str_get(jstr), str[i]));
  }
  util_free(str);
  json_factory_delete(factory);
}

void json_obj_unittest(void) {
  struct json_factory *factory = json_factory_new();
  struct json *obj = json_factory_obj(factory);
  index_t i, count = 100;
  char(*key)[2] = util_malloc_array(sizeof(char[2]), count);
  for (i = 0; i < count; i++) {
    key[i][0] = 'a' + (i * 100) % 26;
    key[i][1] = 0;
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_factory_str(factory, key[i]);
    json_json_obj_set(obj, key[i], val);
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_json_obj_get(obj, key[i]);
    struct json_str *jstr = json_as_str(val);
    assert(jstr);
    assert(util_streq(json_str_get(jstr), key[i]));
  }
  assert(!json_json_obj_get(obj, "0"));
  util_free(key);
  json_factory_delete(factory);
}

void json_unittest(void) {
  json_arr_unittest();
  json_obj_unittest();
}
