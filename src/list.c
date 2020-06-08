#include "list.h"

struct struct_Node;
typedef struct struct_Node Node;
struct struct_Node {
  Node *next;
};
struct struct_List {
  Node node;
};
