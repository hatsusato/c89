#include "str.h"

#include "utility.h"

struct struct_Str {
  char *data;
  Size size;
};

Str *str_new(const char *text, int leng) {
  Str *s = UTILITY_MALLOC(Str);
  assert(0 <= leng);
  s->data = UTILITY_MALLOC_ARRAY(char, leng + 1);
  s->size = leng;
  UTILITY_MEMCPY(char, s->data, text, leng);
  s->data[leng] = 0;
  return s;
}
void str_delete(Str *s) {
  assert(s);
  UTILITY_FREE(s->data);
  UTILITY_FREE(s);
}
Size str_length(const Str *s) {
  return s->size;
}
const char *str_begin(const Str *s) {
  return s->data;
}
const char *str_end(const Str *s) {
  return s->data + s->size;
}
