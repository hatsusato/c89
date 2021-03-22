#ifndef INCLUDE_GUARD_E143C1B6_7F5B_4A0D_A3AC_017C08073B57
#define INCLUDE_GUARD_E143C1B6_7F5B_4A0D_A3AC_017C08073B57

typedef void *VectorElem;
typedef const void *VectorCmpElem;
typedef void (*VectorDestructor)(VectorElem);
typedef int (*VectorCmp)(const VectorCmpElem *, const VectorCmpElem *);

#endif /* INCLUDE_GUARD_E143C1B6_7F5B_4A0D_A3AC_017C08073B57 */
