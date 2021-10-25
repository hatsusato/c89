#include "unittest.h"

#include "dict.h"
#include "util/util.h"

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
    int *val = dict_find(dict, key[i]);
    assert(val && *val == i * 100);
  }
  assert(!dict_find(dict, "abc"));
  util_free(val);
  util_free(key);
  dict_delete(dict);
}
