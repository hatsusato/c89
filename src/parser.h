#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

#define AST_NEW(tag, scanner, x0)               \
  do {                                          \
    x0.vec = ast_new_token(AST_##tag, scanner); \
  } while (0)
#define AST_APPEND0(tag, x0)            \
  do {                                  \
    x0.vec = ast_new_tag(AST_##tag, 0); \
  } while (0)
#define AST_APPEND1(tag, x0, x1)        \
  do {                                  \
    x0.vec = ast_new_tag(AST_##tag, 1); \
    ast_append(x0.vec, x1.vec);         \
  } while (0)
#define AST_APPEND2(tag, x0, x1, x2)    \
  do {                                  \
    x0.vec = ast_new_tag(AST_##tag, 2); \
    ast_append(x0.vec, x1.vec);         \
    ast_append(x0.vec, x2.vec);         \
  } while (0)
#define AST_APPEND3(tag, x0, x1, x2, x3) \
  do {                                   \
    x0.vec = ast_new_tag(AST_##tag, 3);  \
    ast_append(x0.vec, x1.vec);          \
    ast_append(x0.vec, x2.vec);          \
    ast_append(x0.vec, x3.vec);          \
  } while (0)
#define AST_APPEND4(tag, x0, x1, x2, x3, x4) \
  do {                                       \
    x0.vec = ast_new_tag(AST_##tag, 4);      \
    ast_append(x0.vec, x1.vec);              \
    ast_append(x0.vec, x2.vec);              \
    ast_append(x0.vec, x3.vec);              \
    ast_append(x0.vec, x4.vec);              \
  } while (0)
#define AST_TOKEN(tag, x0, token)                    \
  do {                                               \
    x0.vec = ast_new_tag(AST_##tag, 1);              \
    ast_append(x0.vec, ast_new_tag(AST_##token, 0)); \
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
