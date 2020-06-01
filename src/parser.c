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
void ast_set_text(Vector* ast, const char* text, int length) {
  assert(ast && text);
  ast_set_int(ast, length);
  vector_append(ast, text, length);
}
int ast_get_text(const char* ast, const char** text, int* length) {
  int offset = 0;
  assert(ast && text && length);
  offset += ast_get_int(ast, length);
  *text = ast + offset;
  offset += *length;
  return offset;
}
void ast_set_int(Vector* ast, int val) {
  assert(ast);
  vector_append(ast, &val, sizeof(val));
}
int ast_get_int(const char* ast, int* val) {
  assert(ast && val);
  *val = *(int*)ast;
  return sizeof(int);
}
