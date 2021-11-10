#ifndef INCLUDE_GUARD_595231AD_B6B3_42B4_BBB8_682163EA7D87
#define INCLUDE_GUARD_595231AD_B6B3_42B4_BBB8_682163EA7D87

#include "util/type.h"

struct json;

struct json *ir_value_new_global(struct json *);
const char *ir_value_get_name(struct json *);
bool_t ir_value_is_global(struct json *);

#endif /* INCLUDE_GUARD_595231AD_B6B3_42B4_BBB8_682163EA7D87 */
