#ifndef INCLUDE_GUARD_69F25D1A_A2AC_4682_B8B7_83A8EC0E119D
#define INCLUDE_GUARD_69F25D1A_A2AC_4682_B8B7_83A8EC0E119D

typedef const void *CompareExtra, *CompareElem;
typedef void (*CompareDestructor)(CompareExtra);
typedef int (*CompareCmp)(CompareElem, CompareElem, CompareExtra);

#endif /* INCLUDE_GUARD_69F25D1A_A2AC_4682_B8B7_83A8EC0E119D */
