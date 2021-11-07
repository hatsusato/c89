#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

#include "util/type.h"

struct json;

bool_t json_is_null(struct json *);
bool_t json_is_int(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);

#include "json/arr.h"
#include "json/int.h"
#include "json/new.h"
#include "json/null.h"
#include "json/obj.h"
#include "json/str.h"
#include "json/util.h"

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
