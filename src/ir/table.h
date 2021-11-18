#ifndef INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD
#define INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD

#include "json/map_type.h"
#include "util/type.h"

struct json;

struct json *ir_table_new(void);
void ir_table_push(struct json *);
void ir_table_pop(struct json *);
void ir_table_insert(struct json *, const char *, struct json *);
struct json *ir_table_lookup(struct json *, const char *);
struct json *ir_table_make_global(struct json *, struct json *);
void ir_table_insert_global(struct json *, const char *, struct json *);
void ir_table_finish(struct json *);
void ir_table_foreach_global(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_3E579799_CAB2_4118_A2FB_80FF6F20C6DD */
