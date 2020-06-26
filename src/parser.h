#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "ast.h"
#include "parser.tab.h"

AstList parser_init(void);
AstList parser_token(int, yyscan_t);
AstList parser_append0(int);
AstList parser_append1(int, AstList);
AstList parser_append2(int, AstList, AstList);
AstList parser_append3(int, AstList, AstList, AstList);
AstList parser_append4(int, AstList, AstList, AstList, AstList);
AstList parser_binary(AstList, AstList, AstList);
AstList parser_empty(void);
AstList parser_list_empty(int);
AstList parser_list_new(int, AstList);
AstList parser_list_push(AstList, AstList);
AstList parser_list_finish(AstList);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
