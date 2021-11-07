#ifndef INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E
#define INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E

struct convert_extra {
  struct json *module;
  struct json *function;
};

struct json *convert_extra_new_module(void);
void convert_extra_init(struct convert_extra *, struct json *);

#endif /* INCLUDE_GUARD_CB18DD4B_D664_4B99_90FE_A9C9088A348E */
