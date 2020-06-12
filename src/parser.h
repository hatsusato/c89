#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

#define AST_NEW(tag, scanner, x0)                \
  do {                                           \
    x0.list = ast_new_token(AST_##tag, scanner); \
  } while (0)
#define AST_APPEND0(tag, x0)          \
  do {                                \
    x0.list = ast_new_tag(AST_##tag); \
  } while (0)
#define AST_APPEND1(tag, x0, x1)      \
  do {                                \
    x0.list = ast_new_tag(AST_##tag); \
    list_append(x0.list, x1.list);    \
  } while (0)
#define AST_APPEND2(tag, x0, x1, x2)  \
  do {                                \
    x0.list = ast_new_tag(AST_##tag); \
    list_append(x0.list, x1.list);    \
    list_append(x0.list, x2.list);    \
  } while (0)
#define AST_APPEND3(tag, x0, x1, x2, x3) \
  do {                                   \
    x0.list = ast_new_tag(AST_##tag);    \
    list_append(x0.list, x1.list);       \
    list_append(x0.list, x2.list);       \
    list_append(x0.list, x3.list);       \
  } while (0)
#define AST_APPEND4(tag, x0, x1, x2, x3, x4) \
  do {                                       \
    x0.list = ast_new_tag(AST_##tag);        \
    list_append(x0.list, x1.list);           \
    list_append(x0.list, x2.list);           \
    list_append(x0.list, x3.list);           \
    list_append(x0.list, x4.list);           \
  } while (0)
#define AST_TOKEN(tag, x0, token)                   \
  do {                                              \
    x0.list = ast_new_tag(AST_##tag);               \
    list_append(x0.list, ast_new_tag(AST_##token)); \
  } while (0)
#define AST_INIT(dst) \
  do {                \
    dst.list = nil;   \
  } while (0)
#define AST_TAG(dst, tag)              \
  do {                                 \
    dst.list = ast_new_tag(AST_##tag); \
  } while (0)
#define AST_PUSH_TAG(dst, tag)                                \
  do {                                                        \
    dst.list = list_append(dst.list, ast_new_tag(AST_##tag)); \
  } while (0)
#define AST_PUSH(dst, src)                      \
  do {                                          \
    dst.list = list_append(dst.list, src.list); \
  } while (0)
#define AST_EMPTY(dst)      \
  do {                      \
    AST_INIT(dst);          \
    AST_PUSH_TAG(dst, NIL); \
  } while (0)
#define AST_CONS(dst, car, cdr) \
  do {                          \
    AST_INIT(dst);              \
    AST_PUSH(dst, car);         \
    AST_PUSH(dst, cdr);         \
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
List *ast_new_token(int, yyscan_t);
List *ast_new_tag(int);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
