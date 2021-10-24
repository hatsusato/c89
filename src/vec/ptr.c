#include "ptr.h"

#include "array/array.h"
#include "ptr_type.h"
#include "util/util.h"
#include "vec.h"

struct vec_ptr *vec_ptr_new(void) {
  struct vec_ptr *self = util_malloc(sizeof(struct vec_ptr), 1);
  vec_init(&self->vec, sizeof(void *));
  return self;
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_finish(&self->vec);
  util_free(self);
}
index_t vec_ptr_capacity(struct vec_ptr *self) {
  return vec_capacity(&self->vec);
}
index_t vec_ptr_length(struct vec_ptr *self) {
  return vec_length(&self->vec);
}
struct array *vec_ptr_get_array(struct vec_ptr *self) {
  return vec_get_array(&self->vec);
}
void *vec_ptr_at(struct vec_ptr *self, index_t index) {
  return *(void **)vec_at(&self->vec, index);
}
void *vec_ptr_top(struct vec_ptr *self) {
  return vec_ptr_at(self, -1);
}
void vec_ptr_push(struct vec_ptr *self, void *ptr) {
  vec_push(&self->vec, &ptr);
}
void vec_ptr_pop(struct vec_ptr *self) {
  vec_pop(&self->vec);
}
void vec_ptr_clear(struct vec_ptr *self) {
  vec_clear(&self->vec);
}
void vec_ptr_map(struct vec_ptr *self, void (*map)(void *)) {
  index_t index;
  assert(map);
  for (index = 0; index < vec_ptr_length(self); index++) {
    map(vec_ptr_at(self, index));
  }
}
void vec_ptr_sort(struct vec_ptr *self, cmp_t cmp) {
  struct array *array = vec_ptr_get_array(self);
  array_sort(array, cmp);
}
const void *vec_ptr_search(struct vec_ptr *self, const void *key, cmp_t cmp) {
  struct array *array = vec_ptr_get_array(self);
  void **found = array_search(array, &key, cmp);
  return found ? *found : NULL;
}
