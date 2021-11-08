#ifndef INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E
#define INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E

struct convert {
  struct json *module;
  struct json *function;
  struct json *block;
};

struct json *convert_extra_new_module(void);
void convert_init(struct convert *, struct json *);
void convert_push_block(struct convert *);
struct json *convert_push_instr(struct convert *, const char *);
void convert_extra_push_symbol(struct convert *, struct json *, struct json *);
struct json *convert_extra_lookup_symbol(struct convert *, struct json *);

#endif /* INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E */
