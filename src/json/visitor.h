#ifndef INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651
#define INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651

struct json;
struct json_factory;
struct json_visitor;

typedef void (*json_visitor_t)(struct json_visitor *, struct json *);

struct json_visitor {
  json_visitor_t visitor;
  const char *key;
  struct json_factory *factory;
  struct json *result;
  void *extra;
};

void json_visitor_visit(struct json_visitor *, struct json *);

#endif /* INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651 */
