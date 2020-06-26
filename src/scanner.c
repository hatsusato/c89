#include "scanner.h"

#include "list.h"
#include "utility.h"

struct struct_Extra {
  List *ast;
};

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
yyscan_t scanner_new(void) {
  yyscan_t scanner = nil;
  YYSTYPE extra = parser_init();
  int ret = yylex_init_extra(extra, &scanner);
  assert(ret == 0);
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  yylex_destroy(scanner);
}
void scanner_set_ast(yyscan_t scanner, YYSTYPE ast) {
  yyset_extra(ast, scanner);
}
