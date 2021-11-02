#ifndef INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD
#define INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD

enum json_tag {
  JSON_TAG_NULL,
  JSON_TAG_INT,
  JSON_TAG_STR,
  JSON_TAG_ARR,
  JSON_TAG_OBJ,
  JSON_TAG_ANY
};

struct json {
  enum json_tag tag;
  void *json;
};

struct json *json_alloc(enum json_tag, void *);
void json_free(struct json *);
void *json_get(struct json *);
enum json_tag json_tag(struct json *);

#endif /* INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD */
