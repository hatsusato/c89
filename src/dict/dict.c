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
static int dict_cmp(const void *lhs, const void *rhs) {
  const struct dict_entry *const *l = lhs, *const *r = rhs;
  return util_strcmp((*l)->key, (*r)->key);
}
static struct dict_entry *dict_search(struct dict *self, const char *key) {
  struct dict_entry entry = {NULL, NULL};
  entry.key = key;
  return (void *)vec_search(self->vec, &entry, dict_cmp);
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
  struct dict_entry *entry = dict_search(self, key);
  if (entry) {
    entry->val = val;
  } else {
    entry = util_malloc(sizeof(struct dict_entry), 1);
    entry->key = key;
    entry->val = val;
    vec_push(self->vec, entry);
    vec_sort(self->vec, dict_cmp);
  }
}
void *dict_find(struct dict *self, const char *key) {
  const struct dict_entry *found = dict_search(self, key);
  return found ? found->val : NULL;
}
