#include "unittest.h"

#include "factory.h"
#include "json.h"
#include "util/util.h"

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
    json_obj_set(obj, key[i], val);
  }
  for (i = 0; i < count; i++) {
    struct json *val = json_obj_get(obj, key[i]);
    assert(val && json_is_str(val));
    assert(util_streq(json_str_get(val), key[i]));
  }
  assert(!json_obj_get(obj, "0"));
  util_free(key);
  json_factory_delete(factory);
}

void json_unittest(void) {
  json_obj_unittest();
}
