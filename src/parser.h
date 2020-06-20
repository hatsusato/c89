#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

#define AST_INIT(dst) \
  do {                \
    dst = ast_init(); \
  } while (0)
#define AST_TAG(dst, tag)         \
  do {                            \
    dst = ast_new_tag(AST_##tag); \
  } while (0)
#define AST_PUSH_TAG(dst, tag)          \
  do {                                  \
    dst = ast_push_tag(dst, AST_##tag); \
  } while (0)
#define AST_PUSH(dst, src)    \
  do {                        \
    dst = ast_push(dst, src); \
  } while (0)
#define AST_EMPTY(dst)      \
  do {                      \
    AST_INIT(dst);          \
    AST_PUSH_TAG(dst, NIL); \
  } while (0)
#define AST_LIST_CONS(dst, car, cdr) \
  do {                               \
    AST_INIT(dst);                   \
    AST_PUSH(dst, car);              \
    AST_PUSH(dst, cdr);              \
  } while (0)
#define AST_LIST_EMPTY(dst, tag) \
  do {                           \
    AST_TAG(dst, LIST);          \
    AST_PUSH_TAG(dst, tag);      \
    AST_PUSH_TAG(dst, NIL);      \
  } while (0)
#define AST_LIST_EXIST(dst, tag, src) \
  do {                                \
    AST_TAG(dst, LIST);               \
    AST_PUSH_TAG(dst, tag);           \
    AST_PUSH(dst, src);               \
    AST_PUSH_TAG(dst, NIL);           \
  } while (0)

void yyerror(const char *, yyscan_t);
YYSTYPE ast_init(void);
YYSTYPE ast_new_token(int, yyscan_t);
YYSTYPE ast_new_tag(int);
YYSTYPE ast_append0(int);
YYSTYPE ast_append1(int, YYSTYPE);
YYSTYPE ast_append2(int, YYSTYPE, YYSTYPE);
YYSTYPE ast_append3(int, YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE ast_push(YYSTYPE, YYSTYPE);
YYSTYPE ast_push_tag(YYSTYPE, int);
YYSTYPE ast_arity0(int);
YYSTYPE ast_arity1(int);
YYSTYPE ast_arity2(int);
YYSTYPE ast_arity3(int);
YYSTYPE ast_binary(YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE ast_list_empty(int);
YYSTYPE ast_list_new(int, YYSTYPE);
YYSTYPE ast_list_push(YYSTYPE, YYSTYPE);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
