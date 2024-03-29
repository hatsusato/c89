#ifndef INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF
#define INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF

#include "util/type.h"

struct json;
struct json_pair;
struct json_vec;

struct json_vec *json_vec_new(void);
void json_vec_del(struct json_vec *);
index_t json_vec_count(struct json_vec *);
void json_vec_push(struct json_vec *, const char *, struct json *);
struct json_pair *json_vec_at(struct json_vec *, index_t);
void json_vec_sort(struct json_vec *);
struct json_pair *json_vec_search(struct json_vec *, const char *);
struct json_pair *json_vec_find(struct json_vec *, const char *);

#endif /* INCLUDE_GUARD_28ECEBB7_B3F3_4129_987F_AA9D1F2203BF */
