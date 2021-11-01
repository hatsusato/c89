#ifndef INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651
#define INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651

struct json;
struct json_obj;
struct json_visitor;

typedef void (*json_visitor_t)(struct json *, void *);

struct json_visitor {
  json_visitor_t visitor;
  const char *key;
  struct json *result;
  struct json_obj *parent;
  void *extra;
};

void json_visitor_recurse(struct json_visitor *, struct json *);
void json_visitor_visit(json_visitor_t, const char *, struct json *, void *);

#endif /* INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651 */
