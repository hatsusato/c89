#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "parser.tab.h"

void yyerror(const char*, yyscan_t);
void ast_set_top(Vector* top, Vector* ast);
const char* ast_get_top(const char* top, int* length, const char** text);
void ast_set_text(Vector*, const char*, int);
int ast_get_text(const char*, const char**, int*);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
