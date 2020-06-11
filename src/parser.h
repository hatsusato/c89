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

void yyerror(const char *, yyscan_t);
void ast_vec_set_text(Vector *, const char *, int);
const char *ast_vec_get_text(const char *, const char **, int *);
void ast_vec_set_int(Vector *, int);
const char *ast_vec_get_int(const char *, int *);
Vector *ast_vec_new_token(int, yyscan_t);
Vector *ast_vec_new_tag(int, int);
void ast_vec_append(Vector *, Vector *);
void ast_vec_print_text(const char *, int);
const char *ast_vec_print_token(const char *);
const char *ast_vec_print(const char *);

List *ast_new_token(int, yyscan_t);
List *ast_new_tag(int);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
