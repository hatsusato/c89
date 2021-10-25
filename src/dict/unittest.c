#include "unittest.h"

#include "dict.h"
#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

struct dict_entry {
  const char *key;
  void *val;
};

void dict_unittest(void) {
  struct dict *dict = dict_new();
  int i, count = 10;
  char(*key)[2] = util_malloc(sizeof(char[2]), count);
  int *val = util_malloc(sizeof(int), count);
  for (i = 0; i < count; i++) {
    key[i][0] = 'a' + (i * 100) % 26;
    key[i][1] = '\0';
    val[i] = i * 100;
    dict_insert(dict, key[i], val + i);
  }
  for (i = 0; i < count; i++) {
    struct dict_entry *entry = vec_at(dict->vec, i);
    assert(util_streq(entry->key, key[i]));
    assert(*(int *)entry->val == i * 100);
  }
  util_free(val);
  util_free(key);
  dict_delete(dict);
}
