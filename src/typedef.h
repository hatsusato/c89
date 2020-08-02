#ifndef INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A
#define INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A

#include <stddef.h>

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#define true (1)
#define false (0)
typedef int Bool;
typedef unsigned char Byte;
typedef unsigned long PointerBytes;
typedef int Size;
typedef int Index;

typedef const void *ElemType;
typedef int (*Compare)(const ElemType *, const ElemType *);
typedef void (*Destructor)(ElemType);
typedef void (*ForeachMap)(ElemType, void *);

struct struct_Block;
typedef struct struct_Block Block;

struct struct_Declaration;
typedef struct struct_Declaration Declaration;

struct struct_Function;
typedef struct struct_Function Function;

struct struct_Instruction;
typedef struct struct_Instruction Instruction;

struct struct_List;
typedef struct struct_List List;

struct struct_Module;
typedef struct struct_Module Module;

struct struct_Result;
typedef struct struct_Result Result;

struct struct_Set;
typedef struct struct_Set Set;

struct struct_Sexp;
typedef struct struct_Sexp const Sexp;

struct struct_Str;
typedef struct struct_Str Str;

struct struct_Table;
typedef struct struct_Table Table;

struct struct_Value;
typedef struct struct_Value Value;

struct struct_Vector;
typedef struct struct_Vector Vector;

#endif /* INCLUDE_GUARD_E20E6EF6_D4AC_4C0A_A3D6_B4A494B0E59A */
