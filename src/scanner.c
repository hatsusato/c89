#include "scanner.h"

#include "list.h"

struct struct_Extra {
  List *ast;
};

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
