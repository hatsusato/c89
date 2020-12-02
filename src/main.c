#include "ast.h"
#include "ir/stack.h"
#include "print.h"
#include "scanner.h"

static void build(Sexp *ast) {
  Stack *stack = stack_new();
  stack_build(stack, ast);
  stack_print(stack);
  stack_delete(stack);
}

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Sexp *ast = ast_get(scanner_get(scanner));
    print_ast(ast);
    build(ast);
  }
  scanner_delete(scanner);
  return ret;
}
