#ifndef INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF
#define INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF

#include "util/type.h"

struct json;
struct json_vec;

struct json_pair {
  const char *key;
  struct json *val;
};
typedef void (*json_map_t)(struct json_pair *);

struct json_vec *json_vec_new(void);
void json_vec_delete(struct json_vec *);
index_t json_vec_count(struct json_vec *);
void json_vec_push(struct json_vec *, const char *, struct json *);
struct json_pair *json_vec_at(struct json_vec *, index_t);
void json_vec_sort(struct json_vec *);
struct json_pair *json_vec_search(struct json_vec *, const char *);
struct json_pair *json_vec_find(struct json_vec *, const char *);
void json_vec_map(struct json_vec *, json_map_t);

#endif /* INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF */
