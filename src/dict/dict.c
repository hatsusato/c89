#include "dict.h"

#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

struct dict_entry {
  const char *key;
  void *val;
};

static void dict_entry_free(void *entry) {
  util_free(entry);
}

struct dict *dict_new(void) {
  struct dict *self = util_malloc(sizeof(struct dict), 1);
  self->vec = vec_new();
  return self;
}
void dict_delete(struct dict *self) {
  vec_map(self->vec, dict_entry_free);
  vec_delete(self->vec);
  util_free(self);
}
void dict_insert(struct dict *self, const char *key, void *val) {
  struct dict_entry *entry = util_malloc(sizeof(struct dict_entry), 1);
  entry->key = key;
  entry->val = val;
  vec_push(self->vec, entry);
}
