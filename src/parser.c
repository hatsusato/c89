#include "parser.h"

#include <assert.h>
#include <stdio.h>

#include "ast.h"

void yyerror(const char* msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
void ast_set_text(Vector* ast, const char* text, int length) {
  assert(ast && text);
  ast_set_int(ast, length);
  vector_append(ast, text, length);
}
const char* ast_get_text(const char* ast, const char** text, int* length) {
  assert(ast && text && length);
  ast = ast_get_int(ast, length);
  *text = ast;
  ast += *length;
  return ast;
}
void ast_set_int(Vector* ast, int val) {
  assert(ast);
  vector_append(ast, &val, sizeof(val));
}
const char* ast_get_int(const char* ast, int* val) {
  assert(ast && val);
  *val = *(int*)ast;
  return ast += sizeof(int);
}
Vector* ast_new_token(int tag, yyscan_t scanner) {
  const char* text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector* ast = vector_new(1);
  ast_set_int(ast, tag);
  ast_set_text(ast, text, leng);
  return ast;
}
Vector* ast_new_tag(int tag, int arity) {
  Vector* ast = vector_new(1);
  ast_set_int(ast, tag);
  ast_set_int(ast, arity);
  return ast;
}
void ast_append(Vector* ast, Vector* v) {
  vector_append(ast, vector_begin(v), vector_length(v));
  vector_delete(&v);
}
void ast_print_text(const char* text, int length) {
  int i = 0;
  for (i = 0; i < length; ++i) {
    printf("%c", text[i]);
  }
}
const char* ast_print_token(const char* cur) {
  int length = 0;
  const char* text = nil;
  cur = ast_get_text(cur, &text, &length);
  ast_print_text(text, length);
  return cur;
}
const char* ast_print(const char* cur) {
  int tag = 0;
  cur = ast_get_int(cur, &tag);
  printf("[%s:", ast_show(tag));
  if (ast_is_token(tag)) {
    cur = ast_print_token(cur);
  } else {
    int arity = 0;
    cur = ast_get_int(cur, &arity);
    for (; 0 < arity; --arity) {
      cur = ast_print(cur);
    }
  }
  printf("]");
  return cur;
}
