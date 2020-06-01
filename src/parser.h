#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

void yyerror(const char*, yyscan_t);
void ast_set_text(Vector*, const char*, int);
const char* ast_get_text(const char*, const char**, int*);
void ast_set_int(Vector*, int);
const char* ast_get_int(const char*, int*);
Vector* ast_new_token(int, yyscan_t);
Vector* ast_new_tag(int, int);
void ast_append(Vector*, Vector*);
void print_text(const char*, int);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
