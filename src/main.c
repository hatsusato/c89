#include "convert/convert.h"
#include "generate/generate.h"
#include "json/factory.h"
#include "json/json.h"
#include "scanner/parse.h"
#include "unittest.h"
#include "util/util.h"

struct options {
  int argc;
  char **argv;
  bool_t unittest;
};

void options_init(struct options *self, int argc, char *argv[]) {
  self->argc = argc;
  self->argv = argv;
  self->unittest = false;
}

bool_t is_unittest(int argc, char *argv[]) {
  index_t i;
  for (i = 1; i < argc; i++) {
    if (util_streq(argv[i], "--unittest")) {
      return true;
    }
  }
  return false;
}
void compile(void) {
  struct json_factory *factory = json_factory_new();
  struct json *json = scanner_parse(factory);
  if (json_is_null(json)) {
    util_error("ERROR: failed to parse");
  } else {
    convert(factory, json);
    generate(json);
  }
  json_factory_del(factory);
}

int main(int argc, char *argv[]) {
  struct options opt;
  options_init(&opt, argc, argv);
  if (is_unittest(argc, argv)) {
#ifndef NDEBUG
    unittest();
#endif
  } else {
    compile();
  }
  return 0;
}
