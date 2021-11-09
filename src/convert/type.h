#ifndef INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E
#define INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E

struct convert {
  struct json *module;
  struct json *function;
  struct json *block;
};

void convert_init(struct convert *, struct json *);
struct json *convert_new_module(void);
struct json *convert_get_module(struct convert *);
void convert_push_block(struct convert *);
struct json *convert_push_instr(struct convert *, const char *);

#endif /* INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E */
