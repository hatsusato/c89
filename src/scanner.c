#include "scanner.h"

#include "parser.tab.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
};

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(Scanner *scanner) {
  return yyparse(scanner->yyscan);
}
