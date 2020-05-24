#include <stdio.h>

#include "parser.tab.h"
int g_result;

void yyerror(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}
int main(void) {
  yyparse();
  return g_result;
}
