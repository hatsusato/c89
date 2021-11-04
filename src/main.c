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
  bool_t unittest, debug;
};

static void options_parse(struct options *self) {
  index_t i;
  for (i = 1; i < self->argc; i++) {
    const char *opt = self->argv[i];
    if (util_streq(opt, "--unittest")) {
      self->unittest = true;
    } else if (util_streq(opt, "--debug")) {
      self->debug = true;
    }
  }
}
void options_init(struct options *self, int argc, char *argv[]) {
  self->argc = argc;
  self->argv = argv;
  self->unittest = self->debug = false;
  options_parse(self);
}
void compile(bool_t debug) {
  struct json_factory *factory = json_factory_new();
  struct json *json = scanner_parse(factory);
  if (json_is_null(json)) {
    util_error("ERROR: failed to parse");
  } else {
    convert(factory, json);
    generate(json);
    if (debug) {
      json_print(json);
    }
  }
  json_factory_del(factory);
}

int main(int argc, char *argv[]) {
  struct options opt;
  options_init(&opt, argc, argv);
  if (opt.unittest) {
#ifndef NDEBUG
    unittest();
#endif
  } else {
    compile(opt.debug);
  }
  return 0;
}
