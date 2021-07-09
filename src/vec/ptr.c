#include "ptr.h"

#include <assert.h>

#include "type.h"
#include "vec.h"

void vec_ptr_new(struct vec_ptr *self) {
  vec_init(&self->vec, sizeof(void *));
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_finish(&self->vec);
}
index_t vec_ptr_capacity(struct vec_ptr *self) {
  return vec_capacity(&self->vec);
}
index_t vec_ptr_length(struct vec_ptr *self) {
  return vec_length(&self->vec);
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
