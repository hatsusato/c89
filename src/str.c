#include "str.h"

#include "utility.h"

struct struct_String {
  char *data;
  Size size;
};

String *string_new(const char *text, int leng) {
  String *s = UTILITY_MALLOC(String);
  assert(0 <= leng);
  s->data = UTILITY_MALLOC_ARRAY(char, leng + 1);
  s->size = leng;
  UTILITY_MEMCPY(char, s->data, text, leng);
  s->data[leng] = 0;
  return s;
}
void string_delete(String *s) {
  assert(s);
  UTILITY_FREE(s->data);
  UTILITY_FREE(s);
}
Size string_length(const String *s) {
  return s->size;
}
const char *string_begin(const String *s) {
  return s->data;
}
const char *string_end(const String *s) {
  return s->data + s->size;
}
