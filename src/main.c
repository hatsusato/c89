#include <stdio.h>

#include "parser.tab.h"

int main(void) {
  return yyparse();
}
