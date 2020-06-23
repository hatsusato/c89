#include "string.h"

#include <stdlib.h>
#include <string.h>

struct struct_String {
  char* data;
  Size size, capacity;
};

String* string_new(const char* init) {
  String* s = malloc(sizeof(String));
  Size cap = strlen(init) + 1;
  s->data = malloc(cap);
  s->size = cap - 1;
  s->capacity = cap;
  memcpy(s->data, init, s->capacity);
  return s;
}
void string_delete(String* s) {
  assert(s);
  free(s->data);
  free(s);
}
Size string_length(String* s) {
  return s->size;
}
