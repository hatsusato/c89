#include "array.h"

#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "util/util.h"

static const align_t align = sizeof(struct json_pair);

void json_array_insert(struct json_array *self, struct json_pair *base,
                       index_t count) {
  if (0 < count) {
    assert(self->base && base);
    memcpy(self->base + align * self->count, base, align * count);
    self->count += count;
  }
}
void json_array_resize(struct json_array *self, index_t count) {
  struct json_array tmp = {NULL, 0};
  tmp.base = util_malloc_array(align, count);
  json_array_insert(&tmp, self->base, UTIL_MIN(self->count, count));
  UTIL_SWAP(struct json_array, self, &tmp);
  util_free(tmp.base);
}
void json_array_sort(struct json_array *self, cmp_t cmp) {
  if (self->base) {
    qsort(self->base, self->count, align, cmp);
  }
}
struct json_pair *json_array_search(struct json_array *self,
                                    struct json_pair *key, cmp_t cmp) {
  if (self->base) {
    return bsearch(key, self->base, self->count, align, cmp);
  }
  return NULL;
}
