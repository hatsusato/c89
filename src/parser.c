#include "parser.h"

void yyerror(const char* msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "%s\n", msg);
}
