#ifndef INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17
#define INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17

struct json;

void ir_function_init(struct json *, struct json *);
void ir_function_finish(struct json *);
void ir_function_push_block(struct json *);
struct json *ir_function_new_block(struct json *);
struct json *ir_function_new_instr(struct json *, const char *);
struct json *ir_function_new_alloca(struct json *);

#endif /* INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17 */
