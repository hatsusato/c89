#ifndef INCLUDE_GUARD_BDF9C1AF_53CF_4D1F_8A03_23E511410297
#define INCLUDE_GUARD_BDF9C1AF_53CF_4D1F_8A03_23E511410297

#include "util/type.h"

struct json;

struct json *json_arr_new(void);
void json_arr_delete(struct json *);
void json_arr_insert(struct json *, struct json *);
struct json *json_arr_at(struct json *, index_t);

#endif /* INCLUDE_GUARD_BDF9C1AF_53CF_4D1F_8A03_23E511410297 */
