#ifndef INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A
#define INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A

struct struct_List;
typedef struct struct_List List;

struct struct_Result;
typedef struct struct_Result Result;

struct struct_Set;
typedef struct struct_Set Set;
typedef const void *SetElem;
typedef int (*SetCompare)(const SetElem *, const SetElem *);

struct struct_Sexp;
typedef struct struct_Sexp const Sexp;

struct struct_String;
typedef struct struct_String String;

struct struct_SymbolTable;
typedef struct struct_SymbolTable SymbolTable;

struct struct_Vector;
typedef struct struct_Vector Vector;
typedef const void *VectorElem;
typedef void (*VectorDestructor)(VectorElem);

#endif /* INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A */
