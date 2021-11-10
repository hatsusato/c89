#ifndef INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08
#define INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08

#include "util/type.h"

struct json;

struct json *ir_module_new(void);
void ir_module_init(struct json *);
void ir_module_finish(struct json *);
void ir_module_push_scope(struct json *);
void ir_module_pop_scope(struct json *);
void ir_module_push_global(struct json *, struct json *);
bool_t ir_module_is_global_scope(struct json *);
void ir_module_insert_symbol(struct json *, const char *, struct json *);
struct json *ir_module_lookup_symbol(struct json *, const char *);
void ir_module_init_function(struct json *, struct json *);
void ir_module_finish_function(struct json *);

#endif /* INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08 */
