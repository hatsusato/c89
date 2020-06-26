#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser.tab.h"
#include "pretty.h"
#include "print.h"
#include "result.h"
#include "string.h"

void ast_list_free(List *list) {
  void *data = list_data(list);
  if (data) {
    string_delete(data);
  }
}
void print_seq(Result *result) {
  List *ast = result_get_ast(result);
  print_ast(ast, 0);
  printf("\n");
  pretty_print(ast);
  list_delete(ast, ast_list_free);
}

Result *parse() {
  Result *result = result_new();
  yyscan_t scanner = nil;
  int ret = yylex_init_extra(result, &scanner);
  assert(ret == 0);
  yyparse(scanner);
  yylex_destroy(scanner);
  return result;
}

int main(void) {
  Result *result = parse();
  print_seq(result);
  result_delete(result);
  return 0;
}
