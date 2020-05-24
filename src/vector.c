#include "vector.h"

#include <stdlib.h>

struct struct_Vector {
  int *begin;
  int *end;
  int *capacity;
};

Vector *vector_new(void) {
  Vector *v = malloc(sizeof(Vector));
  v->begin = NULL;
  v->end = NULL;
  v->capacity = NULL;
  return v;
}
