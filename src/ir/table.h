#ifndef INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD
#define INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD

#include "util/type.h"

struct json;

struct json *ir_table_new(void);
struct json *ir_table_push(struct json *);
struct json *ir_table_pop(struct json *);
void ir_table_insert(struct json *, const char *, struct json *);
struct json *ir_table_lookup(struct json *, const char *);
bool_t ir_table_is_global(struct json *);

#endif /* INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD */
