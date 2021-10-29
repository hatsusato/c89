#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

#include "util/type.h"

struct json;

struct json *json_null(void);
bool_t json_is_null(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);
const char *json_str_get(struct json *);
struct json *json_arr_get(struct json *, index_t);
void json_arr_set(struct json *, index_t, struct json *);
void json_arr_push(struct json *, struct json *);
struct json *json_obj_get(struct json *, const char *);
void json_obj_set(struct json *, const char *, struct json *);

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
