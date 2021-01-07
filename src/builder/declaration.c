#include "declaration.h"

#include "ast/tag.h"
#include "builder.h"
#include "global.h"
#include "instruction.h"
#include "sexp.h"
#include "type.h"
#include "utility.h"

void builder_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
  builder_ast(builder, sexp_at(ast, 2));
}
void builder_declaration_specifiers(Builder *builder, Sexp *ast) {
  Type *type = builder_type_integer(builder, 32);
  UTILITY_ASSERT(AST_DECLARATION_SPECIFIERS == sexp_get_tag(ast));
  builder_ast_map(builder, ast);
  builder_set_type(builder, type);
}
void builder_init_declarator_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  builder_ast_map(builder, ast);
}
void builder_init_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  UTILITY_ASSERT(2 == sexp_length(ast) || 4 == sexp_length(ast));
  builder_ast(builder, sexp_at(ast, 1));
  if (4 == sexp_length(ast)) {
    Value *dst = builder_get_value(builder), *src;
    builder_ast(builder, sexp_at(ast, 3));
    src = builder_get_value(builder);
    if (builder_is_local(builder)) {
      builder_instruction_store(builder, src, dst);
    } else {
      builder_init_global(builder, dst, src);
    }
  }
}
void builder_storage_class_specifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STORAGE_CLASS_SPECIFIER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_type_specifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPE_SPECIFIER == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
#define DO_HANDLE(type)                               \
  case AST_##type:                                    \
    builder_set_type_spec(builder, TYPE_SPEC_##type); \
    break
    DO_HANDLE(VOID);
    DO_HANDLE(CHAR);
    DO_HANDLE(SHORT);
    DO_HANDLE(INT);
    DO_HANDLE(LONG);
    DO_HANDLE(FLOAT);
    DO_HANDLE(DOUBLE);
    DO_HANDLE(SIGNED);
    DO_HANDLE(UNSIGNED);
#undef DO_HANDLE
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
void builder_struct_or_union_specifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRUCT_OR_UNION_SPECIFIER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_struct_declaration_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRUCT_DECLARATION_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_struct_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRUCT_DECLARATION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_specifier_qualifier_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_SPECIFIER_QUALIFIER_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_struct_declarator_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRUCT_DECLARATION_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_struct_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRUCT_DECLARATION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_enum_specifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ENUM_SPECIFIER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_enumerator_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ENUMERATOR_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_enumerator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ENUMERATOR == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_type_qualifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPE_QUALIFIER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATOR == sexp_get_tag(ast));
  if (2 == sexp_length(ast)) {
    builder_ast(builder, sexp_at(ast, 1));
  } else {
    UTILITY_ASSERT(3 == sexp_length(ast));
    UTILITY_ASSERT(builder_is_local(builder));
    builder_ast(builder, sexp_at(ast, 2));
  }
}
void builder_direct_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  if (2 == sexp_length(ast)) {
    const char *symbol = identifier_symbol(sexp_at(ast, 1));
    if (builder_is_local(builder)) {
      builder_instruction_alloca(builder, symbol);
    } else {
      builder_new_global(builder, symbol);
    }
  } else {
    UTILITY_ASSERT(4 == sexp_length(ast));
    UTILITY_ASSERT(builder_is_local(builder));
    builder_ast(builder, sexp_at(ast, 2));
  }
}
void builder_pointer(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_POINTER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_type_qualifier_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPE_QUALIFIER_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_parameter_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_PARAMETER_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_parameter_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_PARAMETER_DECLARATION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_identifier_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_IDENTIFIER_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_type_name(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPE_NAME == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_abstract_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ABSTRACT_DECLARATOR == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_direct_abstract_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DIRECT_ABSTRACT_DECLARATOR == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_typedef_name(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPEDEF_NAME == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_initializer(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INITIALIZER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_initializer_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INITIALIZER_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
