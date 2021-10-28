#include "array.h"

#include <string.h>

#include "type.h"
#include "util/util.h"

void json_array_insert(struct json_array *self, const struct json *base,
                       index_t count) {
  static const align_t align = sizeof(struct json);
  if (0 < count) {
    assert(self->base && base);
    memcpy(self->base + align * self->count, base, align * count);
    self->count += count;
  }
}
void json_array_resize(struct json_array *self, index_t count) {
  static const align_t align = sizeof(struct json);
  struct json_array tmp = {NULL, 0};
  tmp.base = util_malloc_array(align, count);
  json_array_insert(&tmp, self->base, UTIL_MIN(self->count, count));
  UTIL_SWAP(struct json_array, self, &tmp);
  util_free(tmp.base);
}
