#ifndef INCLUDE_GUARD_3B393E86_0AF1_4C94_960B_A6CEAC5B0F4D
#define INCLUDE_GUARD_3B393E86_0AF1_4C94_960B_A6CEAC5B0F4D

struct json;

enum json_tag {
  JSON_TAG_NULL,
  JSON_TAG_INT,
  JSON_TAG_STR,
  JSON_TAG_ARR,
  JSON_TAG_OBJ
};

enum json_tag json_tag(struct json *);
void *json_data(struct json *);

#endif /* INCLUDE_GUARD_3B393E86_0AF1_4C94_960B_A6CEAC5B0F4D */