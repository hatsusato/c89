#include "scanner.h"

#include "ast/ast.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Scanner {
  Ast *ast;
  Set *typedefs;
};

Scanner *scanner_new(Ast *ast) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  scanner->ast = ast;
  scanner->typedefs = set_new(NULL, NULL);
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  set_delete(scanner->typedefs);
  UTILITY_FREE(scanner);
}
const char *scanner_symbol(Scanner *scanner, const char *text, Size leng) {
  return ast_symbol(scanner->ast, text, leng);
}
Bool scanner_exists(Scanner *scanner, const char *symbol) {
  return set_find(scanner->typedefs, symbol) != NULL;
}
void scanner_register(Scanner *scanner, const char *symbol) {
  if (!scanner_exists(scanner, symbol)) {
    set_insert(scanner->typedefs, symbol);
  }
}
void scanner_finish(Scanner *scanner, Sexp *ast) {
  ast_set(scanner->ast, ast);
}
