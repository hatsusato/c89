#include "string.h"

#include <stdlib.h>
#include <string.h>

struct struct_String {
  char* data;
  Size size, capacity;
};

String* string_new(const char* init) {
  return string_new_s(init, strlen(init));
}
String* string_new_s(const char* text, int leng) {
  String* s = malloc(sizeof(String));
  s->data = malloc(leng + 1);
  s->size = leng;
  s->capacity = leng + 1;
  memcpy(s->data, text, s->capacity);
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
char* string_begin(String* s) {
  return s->data;
}
char* string_end(String* s) {
  return &s->data[s->size];
}
