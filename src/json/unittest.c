#include "unittest.h"

#include "json.h"
#include "util/util.h"

void json_arr_unittest(void) {
  struct json *json = json_new_arr();
  index_t i, count = 100;
  char(*str)[2] = util_malloc_array(count, sizeof(char[2]));
  for (i = 0; i < count; i++) {
    str[i][0] = 'a' + (i * 100) % 26;
    str[i][1] = 0;
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_new_str(str[i]);
    json_arr_push(json, val);
    json_del(val);
  }
  for (i = 0; i < count; i++) {
    struct json *elem = json_arr_at(json, i);
    assert(util_streq(json_str_get(elem), str[i]));
    UTIL_UNUSED(elem);
  }
  util_free(str);
  json_del(json);
}

void json_obj_unittest(void) {
  struct json *json = json_new_obj();
  index_t i, count = 100;
  char(*key)[2] = util_malloc_array(count, sizeof(char[2]));
  for (i = 0; i < count; i++) {
    key[i][0] = 'a' + (i * 100) % 26;
    key[i][1] = 0;
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_new_str(key[i]);
    json_obj_insert(json, key[i], val);
    json_del(val);
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_obj_get(json, key[i]);
    assert(util_streq(json_str_get(val), key[i]));
    UTIL_UNUSED(val);
  }
  assert(!json_obj_has(json, "0"));
  util_free(key);
  json_del(json);
}

void json_unittest(void) {
  json_arr_unittest();
  json_obj_unittest();
}
