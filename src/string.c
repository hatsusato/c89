#include "string.h"

#include <stdlib.h>
#include <string.h>

#include "utility.h"

struct struct_String {
  char *data;
  Size size;
};

String *string_new(const char *init) {
  return string_new_s(init, strlen(init));
}
String *string_new_s(const char *text, int leng) {
  String *s = malloc(sizeof(String));
  assert(0 <= leng);
  s->data = malloc(leng + 1);
  s->size = leng;
  memcpy(s->data, text, leng);
  s->data[leng] = 0;
  return s;
}
void string_delete(String *s) {
  assert(s);
  free(s->data);
  free(s);
}
Size string_length(String *s) {
  return s->size;
}
char *string_begin(String *s) {
  return s->data;
}
char *string_end(String *s) {
  return &s->data[s->size];
}
