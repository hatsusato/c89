#ifndef INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD
#define INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD

#include "util/type.h"

struct json_arr;
struct json_obj;
struct json_str;
struct json_vec;

enum json_tag { JSON_TAG_NULL, JSON_TAG_STR, JSON_TAG_ARR, JSON_TAG_OBJ };

struct json {
  enum json_tag tag;
  struct json_str *str;
  struct json_arr *arr;
  struct json_obj *obj;
};

#endif /* INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD */
