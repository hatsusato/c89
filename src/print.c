#include "print.h"

#include <ctype.h>

#include "ast/tag.h"
#include "sexp.h"
#include "utility.h"

static void print_sexp(FILE *, Sexp *, int);
static void print_sexp_list(FILE *fp, Sexp *sexp, int indent) {
  assert(sexp_is_pair(sexp));
  print_sexp(fp, sexp_car(sexp), indent);
  for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    print_newline(fp);
    print_indent(fp, indent);
    print_sexp(fp, sexp_car(sexp), indent);
  }
}

void print_indent(FILE *fp, int indent) {
  for (; 0 < indent; --indent) {
    print_message(fp, " ");
  }
}
void print_newline(FILE *fp) {
  print_message(fp, "\n");
}
void print_message(FILE *fp, const char *msg) {
  if (msg) {
    fprintf(fp, "%s", msg);
  }
}
void print_number(FILE *fp, int num) {
  fprintf(fp, "%d", num);
}
void print_verbatim(FILE *fp, const char *text, int leng) {
  int i = 0;
  for (i = 0; i < leng; ++i) {
    char c = text[i];
    if (isprint(c)) {
      fprintf(fp, "%c", c);
    } else {
      fprintf(fp, "\\x%02x", (unsigned char)c);
    }
  }
}
void print_symbol(FILE *fp, Sexp *sexp) {
  const char *msg = NULL;
  if (sexp_is_symbol(sexp)) {
    msg = sexp_get_symbol(sexp);
  } else if (sexp_is_number(sexp)) {
    msg = ast_show(sexp_get_number(sexp));
  }
  print_message(fp, msg);
}
static void print_sexp(FILE *fp, Sexp *sexp, int indent) {
  const char *prefix = "(", *suffix = ")";
  if (sexp_is_pair(sexp)) {
    print_message(fp, prefix);
    print_sexp_list(fp, sexp, indent + 1);
    print_message(fp, suffix);
  } else {
    if (sexp_is_symbol(sexp)) {
      prefix = suffix = "\"";
    } else if (sexp_is_number(sexp)) {
      prefix = suffix = "'";
    }
    print_message(fp, prefix);
    print_symbol(fp, sexp);
    print_message(fp, suffix);
  }
}
void print_ast(Sexp *ast) {
  FILE *fp = stderr;
  print_sexp(fp, ast, 0);
  print_newline(fp);
}
