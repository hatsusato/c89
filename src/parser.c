#include "parser.h"

#include <assert.h>
#include <stdio.h>

void yyerror(const char* msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
void ast_set_top(Vector* top, Vector* ast) {
  if (!top) {
    fprintf(stderr, "empty top\n");
  } else if (!ast) {
    fprintf(stderr, "empty ast\n");
  } else {
    int leng = vector_length(ast);
    const char* text = vector_begin(ast);
    vector_append(top, &leng, sizeof(leng));
    vector_append(top, text, leng);
  }
}
const char* ast_get_top(const char* top, int* length, const char** text) {
  assert(top && length && text);
  *length = *(int*)top;
  top += sizeof(int);
  *text = top;
  top += *length;
  return top;
}
