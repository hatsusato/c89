#include "pretty.h"

#include <assert.h>
#include <stdio.h>

#include "ast.h"
#include "print.h"
#include "utility.h"

typedef struct {
  List *head, *tail;
} Pretty;

List *pretty_convert(Pretty *pretty, List *ast, int indent);

static void pretty_string(const char *s) {
  printf("%s", s);
}
static void pretty_blank(void) {
  pretty_string(" ");
}
static void pretty_newline(void) {
  pretty_string("\n");
}
static void pretty_tag(int tag) {
  pretty_string(ast_show(tag));
}
static List *pretty_print2(List *ast, int indent, const char *delim1) {
  ast = pretty_print(ast, indent);
  pretty_string(delim1);
  return pretty_print(ast, indent);
}
static List *pretty_print3(List *ast, int indent, const char *delim1,
                           const char *delim2) {
  ast = pretty_print2(ast, indent, delim1);
  pretty_string(delim2);
  return pretty_print(ast, indent);
}
static List *pretty_print4(List *ast, int indent, const char *delim1,
                           const char *delim2, const char *delim3) {
  ast = pretty_print3(ast, indent, delim1, delim2);
  pretty_string(delim3);
  return pretty_print(ast, indent);
}
static List *pretty_token(List *ast, int indent) {
  (void)indent;
  ast = list_next(ast);
  return print_data(ast);
}
static List *pretty_list(List *ast, int indent) {
  const char *delims[] = {"", "", ""};
  switch (list_tag(ast)) {
  case AST_SPECIFIER_QUALIFIER_LIST:
  case AST_TYPE_QUALIFIER_LIST:
  case AST_STATEMENT_LIST:
    break;
  case AST_DECLARATION_SPECIFIERS:
    delims[1] = " ";
    break;
  case AST_STRUCT_DECLARATION_LIST:
    ++indent;
    delims[0] = "\n";
    break;
  case AST_DECLARATION_LIST:
    delims[0] = "\n";
    break;
  case AST_TRANSLATION_UNIT:
    delims[1] = "\n";
    break;
  case AST_IDENTIFIER_LIST:
    delims[0] = "(";
    delims[1] = ", ";
    delims[2] = ")";
    break;
  case AST_ENUMERATOR_LIST:
  case AST_INIT_DECLARATOR_LIST:
  case AST_STRUCT_DECLARATOR_LIST:
  case AST_INITIALIZER_LIST:
  case AST_ARGUMENT_EXPRESSION_LIST:
  case AST_PARAMETER_LIST:
    delims[1] = ", ";
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  if (AST_NIL != list_tag(ast)) {
    ast = pretty_print(ast, indent);
  }
  while (AST_NIL != list_tag(ast)) {
    printf("%s", delims[1]);
    ast = pretty_print(ast, indent);
  }
  printf("%s", delims[2]);
  return list_next(ast);
}
static List *pretty_binary(List *ast, int indent) {
  int op = 0;
  assert(AST_ARITY0 == list_tag(ast));
  ast = list_next(ast);
  op = list_tag(ast);
  ast = list_next(ast);
  ast = pretty_print(ast, indent);
  pretty_blank();
  pretty_tag(op);
  pretty_blank();
  ast = pretty_print(ast, indent);
  return ast;
}
static List *pretty_arity0(List *ast, int indent) {
  (void)indent;
  printf("%s", ast_show(list_tag(ast)));
  if (AST_COMMA == list_tag(ast)) {
    printf(" ");
  }
  return list_next(ast);
}
static List *pretty_arity1(List *ast, int indent) {
  const char *delims[] = {"", ""};
  int indents[] = {0, 0};
  switch (list_tag(ast)) {
  case AST_UNARY_EXPRESSION:
  case AST_CONSTANT_EXPRESSION:
  case AST_OLD:
  case AST_PARAMETER_DECLARATION:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_TYPEDEF_NAME:
  case AST_STATEMENT:
  case AST_EXTERNAL_DECLARATION:
  case AST_FUNCTION_DEFINITION:
  case AST_STORAGE_CLASS_SPECIFIER:
  case AST_TYPE_SPECIFIER:
  case AST_STRUCT_DECLARATOR:
  case AST_ENUMERATOR:
  case AST_DECLARATOR:
  case AST_GOTO:
  case AST_TYPE_QUALIFIER:
    break;
  case AST_INIT_DECLARATOR:
    delims[0] = " ";
    break;
  case AST_INITIALIZER:
    delims[0] = "{";
    delims[1] = "}";
    break;
  case AST_PARAMETER_TYPE_LIST:
    delims[1] = ", ...";
    break;
  case AST_ENUM_SPECIFIER:
    delims[0] = "enum ";
    break;
  case AST_ARROW:
    delims[0] = "->";
    break;
  case AST_ARRAY:
    delims[0] = "[";
    delims[1] = "]";
    break;
  case AST_DIRECT_ABSTRACT_DECLARATOR:
  case AST_CALL:
  case AST_DIRECT_DECLARATOR:
  case AST_PRIMARY_EXPRESSION:
    delims[0] = "(";
    delims[1] = ")";
    break;
  case AST_CASE:
    delims[0] = "case ";
    break;
  case AST_SIZEOF:
    delims[0] = "sizeof(";
    delims[1] = ")";
    break;
  case AST_DECLARATION:
    indents[0] = indent;
    delims[1] = ";\n";
    break;
  case AST_RETURN:
    delims[0] = "return ";
    break;
  case AST_SELECTION_STATEMENT:
  case AST_ITERATION_STATEMENT:
    indents[0] = indent;
    delims[1] = "\n";
    break;
  case AST_JUMP_STATEMENT:
    indents[0] = indent;
    delims[1] = ";\n";
    break;
  case AST_EXPRESSION_STATEMENT:
    indents[0] = indent;
    delims[1] = ";\n";
    break;
  case AST_PERIOD:
    delims[0] = ".";
    break;
  case AST_POINTER:
    delims[0] = "*";
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  print_indent(indents[0]);
  printf("%s", delims[0]);
  ast = pretty_print(ast, indent);
  print_indent(indents[1]);
  printf("%s", delims[1]);
  return ast;
}
List *pretty_ast(List *ast, int indent, int arity) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_CAST_EXPRESSION:
    pretty_tag(AST_LEFT_PAREN);
    return pretty_print2(ast, indent, ")");
  case AST_DECLARATION:
    print_indent(indent);
    ast = pretty_print2(ast, indent, "");
    pretty_tag(AST_SEMICOLON);
    pretty_newline();
    return ast;
  case AST_INIT_DECLARATOR:
    pretty_blank();
    return pretty_print2(ast, indent, " = ");
  case AST_STRUCT_DECLARATION:
    print_indent(indent);
    ast = pretty_print2(ast, indent, " ");
    pretty_tag(AST_SEMICOLON);
    pretty_newline();
    return ast;
  case AST_STRUCT_DECLARATOR:
    return pretty_print2(ast, indent, " : ");
  case AST_ENUM_SPECIFIER:
    pretty_tag(AST_ENUM);
    pretty_blank();
    ast = pretty_print2(ast, indent, " {");
    pretty_tag(AST_RIGHT_BRACE);
    return ast;
  case AST_ENUMERATOR:
    pretty_blank();
    return pretty_print2(ast, indent, " = ");
  case AST_POINTER:
    pretty_tag(AST_ASTERISK);
    return pretty_print2(ast, indent, "");
  case AST_PARAMETER_DECLARATION:
    pretty_blank();
    return pretty_print2(ast, indent, "");
  case AST_LABELED_STATEMENT:
    print_indent(indent - 1);
    return pretty_print2(ast, indent, ":\n");
  case AST_COMPOUND_STATEMENT:
    pretty_tag(AST_LEFT_BRACE);
    ast = pretty_print2(ast, indent + 1, "");
    print_indent(indent);
    pretty_tag(AST_RIGHT_BRACE);
    return ast;
  case AST_SWITCH:
    pretty_tag(AST_SWITCH);
    pretty_blank();
    pretty_tag(AST_LEFT_PAREN);
    return pretty_print2(ast, indent, ") ");
  case AST_WHILE:
    pretty_tag(AST_WHILE);
    pretty_blank();
    pretty_tag(AST_LEFT_PAREN);
    return pretty_print2(ast, indent, ") ");
  case AST_DO:
    ast = pretty_print2(ast, indent, "while (");
    pretty_tag(AST_RIGHT_PAREN);
    pretty_tag(AST_SEMICOLON);
    return ast;
  case AST_POSTFIX_EXPRESSION:
  case AST_UNARY_EXPRESSION:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
    return pretty_print2(ast, indent, "");
  case AST_BINARY:
    return pretty_binary(ast, indent);
  case AST_CONDITIONAL_EXPRESSION:
    return pretty_print3(ast, indent, " ? ", " : ");
  case AST_FUNCTION_DEFINITION:
    return pretty_print3(ast, indent, " ", " ");
  case AST_IF:
    switch (arity) {
    case 2:
      pretty_tag(AST_IF);
      pretty_blank();
      pretty_tag(AST_LEFT_PAREN);
      return pretty_print2(ast, indent, ") ");
    case 3:
      pretty_tag(AST_IF);
      pretty_blank();
      pretty_tag(AST_LEFT_PAREN);
      return pretty_print3(ast, indent, ") ", " else ");
    default:
      assert(0);
      return ast;
    }
  case AST_STRUCT_OR_UNION_SPECIFIER:
    switch (arity) {
    case 2:
      return pretty_print2(ast, indent, " ");
    case 3:
      ast = pretty_print3(ast, indent, " ", " {");
      print_indent(indent);
      pretty_tag(AST_RIGHT_BRACE);
      return ast;
    default:
      assert(0);
      return ast;
    }
  case AST_FOR:
    pretty_tag(AST_FOR);
    pretty_blank();
    pretty_tag(AST_LEFT_PAREN);
    return pretty_print4(ast, indent, "; ", "; ", ") ");
  case AST_OLD:
    switch (arity) {
    case 2:
      return pretty_print2(ast, indent, "");
    case 3:
      return pretty_print3(ast, indent, "", "");
    case 4:
      return pretty_print4(ast, indent, " ", "", "");
    default:
      assert(0);
      return ast;
    }
  default:
    assert(0);
    return ast;
  }
}

List *pretty_print(List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    return pretty_token(ast, indent);
  case AST_LIST:
    return pretty_list(ast, indent);
  case AST_ARITY0:
    return pretty_arity0(ast, indent);
  case AST_ARITY1:
    return pretty_arity1(ast, indent);
  case AST_ARITY2:
    return pretty_ast(ast, indent, 2);
  case AST_ARITY3:
    return pretty_ast(ast, indent, 3);
  case AST_ARITY4:
    return pretty_ast(ast, indent, 4);
  default:
    assert(0);
  }
  return ast;
}

void pretty_push(Pretty *pretty, int tag, void *data) {
  assert(pretty);
  if (pretty->tail) {
    list_insert(pretty->tail, list_new(tag, data));
    pretty->tail = list_next(pretty->tail);
  } else {
    pretty->head = pretty->tail = list_new(tag, data);
  }
}
void pretty_push_tag(Pretty *pretty, int tag) {
  assert(pretty);
  pretty_push(pretty, tag, nil);
}
List *pretty_convert_token(Pretty *pretty, List *ast) {
  assert(pretty);
  ast = list_next(ast);
  pretty_push(pretty, list_tag(ast), list_data(ast));
  return list_next(ast);
}
List *pretty_convert_list(Pretty *pretty, List *ast, int indent, int delim) {
  assert(pretty);
  if (AST_NIL != list_tag(ast)) {
    ast = pretty_convert(pretty, ast, indent);
  }
  while (AST_NIL != list_tag(ast)) {
    if (AST_NIL != delim) {
      pretty_push_tag(pretty, delim);
    }
    ast = pretty_convert(pretty, ast, indent);
  }
  return ast;
}
