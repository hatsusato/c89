#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

#include "util/type.h"

struct json;
struct json_arr;
struct json_str;

struct json *json_null(void);
bool_t json_is_null(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);
index_t json_count(struct json *);
struct json_str *json_as_str(struct json *);
struct json_arr *json_as_arr(struct json *);
struct json *json_json_obj_get(struct json *, const char *);
void json_json_obj_set(struct json *, const char *, struct json *);
const char *json_json_obj_key(struct json *, index_t);
struct json *json_json_obj_val(struct json *, index_t);
void json_print(struct json *);

#include "json/arr.h"
#include "json/str.h"

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
