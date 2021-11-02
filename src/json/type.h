#ifndef INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD
#define INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD

#include "tag.h"

struct json {
  enum json_tag tag;
  void *json;
};

struct json *json_alloc(enum json_tag, void *);
void json_free(struct json *);
void *json_get(struct json *);

#endif /* INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD */
