#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

#include "util/type.h"

struct json;
struct json_arr;
struct json_int;
struct json_obj;
struct json_str;

bool_t json_is_null(struct json *);
bool_t json_is_int(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);
struct json_int *json_as_int(struct json *);
struct json_str *json_as_str(struct json *);
struct json_arr *json_as_arr(struct json *);
struct json_obj *json_as_obj(struct json *);
void json_print(struct json *);
void json_set(struct json *, const char *, struct json *);
bool_t json_has(struct json *, const char *);
struct json *json_get(struct json *, const char *);

#include "json/arr.h"
#include "json/int.h"
#include "json/new.h"
#include "json/null.h"
#include "json/obj.h"
#include "json/str.h"

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
