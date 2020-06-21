#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

void yyerror(const char *, yyscan_t);
YYSTYPE parser_init(void);
YYSTYPE parser_token(int, yyscan_t);
YYSTYPE parser_append0(int);
YYSTYPE parser_append1(int, YYSTYPE);
YYSTYPE parser_append2(int, YYSTYPE, YYSTYPE);
YYSTYPE parser_append3(int, YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE parser_append4(int, YYSTYPE, YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE parser_binary(YYSTYPE, YYSTYPE, YYSTYPE);
YYSTYPE parser_empty(void);
YYSTYPE parser_list_empty(int);
YYSTYPE parser_list_new(int, YYSTYPE);
YYSTYPE parser_list_push(YYSTYPE, YYSTYPE);
YYSTYPE parser_list_finish(YYSTYPE);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
