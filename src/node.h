#ifndef INCLUDE_GUARD_B708D97B_CAA0_46DF_A61B_61DC00CAC93F
#define INCLUDE_GUARD_B708D97B_CAA0_46DF_A61B_61DC00CAC93F

#include "typedef.h"

struct struct_Node;
typedef struct struct_Node Node;

Node *node_new(ElemType, Node *);
Node *node_delete(Node *, Destructor);
void node_insert(Node *, Node *);

#endif /* INCLUDE_GUARD_B708D97B_CAA0_46DF_A61B_61DC00CAC93F */
