#include "parse.h"

#include "scanner/parser/yyscan.h"
#include "scanner/scanner.h"

int scanner_parse(Ast *ast) {
  Scanner *scanner = scanner_new(ast);
  int ret = yyscan_parse(scanner);
  scanner_delete(scanner);
  return ret;
}
