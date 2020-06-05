#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

#define AST_NEW(tag, scanner, x0)           \
  do {                                      \
    x0 = ast_new_token(AST_##tag, scanner); \
  } while (0)
#define AST_APPEND0(tag, x0)        \
  do {                              \
    x0 = ast_new_tag(AST_##tag, 0); \
  } while (0)
#define AST_APPEND1(tag, x0, x1)    \
  do {                              \
    x0 = ast_new_tag(AST_##tag, 1); \
    ast_append(x0, x1);             \
  } while (0)
#define AST_APPEND2(tag, x0, x1, x2) \
  do {                               \
    x0 = ast_new_tag(AST_##tag, 2);  \
    ast_append(x0, x1);              \
    ast_append(x0, x2);              \
  } while (0)
#define AST_APPEND3(tag, x0, x1, x2, x3) \
  do {                                   \
    x0 = ast_new_tag(AST_##tag, 3);      \
    ast_append(x0, x1);                  \
    ast_append(x0, x2);                  \
    ast_append(x0, x3);                  \
  } while (0)

void yyerror(const char*, yyscan_t);
void ast_set_text(Vector*, const char*, int);
const char* ast_get_text(const char*, const char**, int*);
void ast_set_int(Vector*, int);
const char* ast_get_int(const char*, int*);
Vector* ast_new_token(int, yyscan_t);
Vector* ast_new_tag(int, int);
void ast_append(Vector*, Vector*);
void ast_print_text(const char*, int);
const char* ast_print_token(const char*);
const char* ast_print(const char*);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
