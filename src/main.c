#include <stdio.h>

#include "parser.tab.h"

int main(void) {
  int token = 0;
  while (0 != (token = yylex())) {
    printf("%s\n", show_token(token));
  }
  return 0;
}
