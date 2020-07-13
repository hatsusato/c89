#include "str.h"

#include "utility.h"

struct struct_Str {
  char *data;
  Size size;
};

Str *string_new(const char *text, int leng) {
  Str *s = UTILITY_MALLOC(Str);
  assert(0 <= leng);
  s->data = UTILITY_MALLOC_ARRAY(char, leng + 1);
  s->size = leng;
  UTILITY_MEMCPY(char, s->data, text, leng);
  s->data[leng] = 0;
  return s;
}
void string_delete(Str *s) {
  assert(s);
  UTILITY_FREE(s->data);
  UTILITY_FREE(s);
}
Size string_length(const Str *s) {
  return s->size;
}
const char *string_begin(const Str *s) {
  return s->data;
}
const char *string_end(const Str *s) {
  return s->data + s->size;
}
