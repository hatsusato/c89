#ifndef INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E
#define INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E

struct convert_extra {
  struct json *module;
  struct json *function;
  struct json *block;
};

struct json *convert_extra_new_module(void);
struct json *convert_extra_new_instr(const char *);
void convert_extra_init(struct convert_extra *, struct json *);
void convert_extra_push_block(struct convert_extra *);
void convert_extra_push_instr(struct convert_extra *, struct json *);
void convert_extra_push_symbol(struct convert_extra *, struct json *,
                               struct json *);
struct json *convert_extra_lookup_symbol(struct convert_extra *, struct json *);

#endif /* INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E */
