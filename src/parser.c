#include "parser.h"

#include <assert.h>
#include <stdio.h>

void yyerror(const char* msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
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
Vector* ast_new_token(int tag, yyscan_t scanner) {
  const char* text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector* ast = vector_new(1);
  ast_set_int(ast, tag);
  ast_set_text(ast, text, leng);
  return ast;
}
