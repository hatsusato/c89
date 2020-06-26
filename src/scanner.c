#include "scanner.h"

#include "utility.h"

typedef struct {
  List *ast;
} Extra;

static Extra *extra_new(void) {
  Extra *extra = malloc(sizeof(Extra));
  extra->ast = nil;
  return extra;
}
static void extra_delete(Extra *extra) {
  assert(extra);
  free(extra);
}

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
List *scanner_get_ast(yyscan_t scanner) {
  YY_EXTRA_TYPE extra = yyget_extra(scanner);
  return extra.list;
}
void scanner_set_ast(yyscan_t scanner, YYSTYPE ast) {
  yyset_extra(ast, scanner);
}
