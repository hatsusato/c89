#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

void yyerror(const char *, yyscan_t);
YYSTYPE ast_init(void);
YYSTYPE ast_new_token(int, yyscan_t);
YYSTYPE ast_new_tag(int);
YYSTYPE ast_append0(int);
YYSTYPE ast_append1(int, YYSTYPE);
YYSTYPE ast_append2(int, YYSTYPE, YYSTYPE);
YYSTYPE ast_append3(int, YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE ast_append4(int, YYSTYPE, YYSTYPE, YYSTYPE, YYSTYPE);
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
void ast_list_finish(YYSTYPE);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
