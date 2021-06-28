#include "ptr.h"

#include "type.h"
#include "util/buffer.h"
#include "vec.h"

static void vec_ptr_destruct(struct vec_ptr *self, void *ptr) {
  if (self->dtor) {
    (self->dtor)(ptr);
  }
}

void vec_ptr_new(struct vec_ptr *self, void (*dtor)(void *)) {
  vec_new(&self->vec, sizeof(void *));
  self->dtor = dtor;
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_ptr_clear(self);
  vec_delete(&self->vec);
  self->dtor = NULL;
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
  index_t index, length = vec_ptr_length(self);
  for (index = length - 1; 0 <= index; index--) {
    vec_ptr_destruct(self, vec_ptr_at(self, index));
  }
  vec_clear(&self->vec);
}
