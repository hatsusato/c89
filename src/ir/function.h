#ifndef INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17
#define INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17

#include "json/map_type.h"

struct json;

struct json *ir_function_new(struct json *);
void ir_function_init(struct json *, struct json *);
void ir_function_finish(struct json *);
struct json *ir_function_get_table(struct json *);
struct json *ir_function_make_instr(struct json *, const char *);
struct json *ir_function_make_alloca(struct json *);
struct json *ir_function_get_block(struct json *);
void ir_function_next_block(struct json *, struct json *);
void ir_function_set_next(struct json *, struct json *);
struct json *ir_function_get_next(struct json *);
void ir_function_set_switch(struct json *, struct json *);
struct json *ir_function_get_switch(struct json *);
void ir_function_set_name(struct json *, struct json *);
const char *ir_function_get_name(struct json *);
void ir_function_foreach(struct json *, json_map_t, void *);
void ir_function_push_return_block(struct json *, struct json *);

#endif /* INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17 */
