#!/usr/bin/make -f

builddir := build
target := $(builddir)/main.out

srcs != git ls-files src/*.c lib/*.c
objs := $(srcs:%.c=$(builddir)/%.o)
deps := $(objs:%.o=%.d)
scanner/objs := $(addprefix $(builddir)/lib/scanner/,parser.o scanner.o)
lex/src := lib/scanner/lexer.l
yacc/src := lib/scanner/parser.y
lex/prefix := $(lex/src:%.l=$(builddir)/%)
yacc/prefix := $(yacc/src:%.y=$(builddir)/%)
meds/lex := $(lex/prefix).c $(lex/prefix).h
meds/yacc := $(yacc/prefix).tab.c $(yacc/prefix).tab.h
meds/srcs := $(filter %.c,$(meds/lex) $(meds/yacc))
meds/objs := $(meds/srcs:%.c=%.o)
meds/deps := $(meds/objs:%.o=%.d)

ldflags =
cflags = -Wall -Wextra -ansi -pedantic -Iinclude
dflags = $(cflags) -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
lflags := --header-file=$(lex/prefix).h --outfile=$(lex/prefix).c
yflags := -d -b $(yacc/prefix)

ifeq (,$(wildcard .develop))
cflags += -O3 -DNDEBUG
else
cflags += -O0 -g
endif

.SUFFIXES:

.PHONY: all
all: $(target)

$(target): $(objs) $(meds/objs)
	$(CC) $(ldflags) $^ -o $@

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

$(meds/lex): $(lex/src) $(yacc/prefix).tab.h
	@mkdir -p $(@D)
	flex $(lflags) $<

$(meds/yacc): $(yacc/src)
	@mkdir -p $(@D)
	bison $(yflags) $<

$(scanner/objs): $(meds/lex) $(meds/yacc)
$(scanner/objs): cflags += -I$(@D)

$(meds/objs): %.o: %.c
	$(CC) $(cflags) -c $< -o $@

$(meds/deps): %.d: %.c
	$(CC) $(dflags) $<

-include $(deps) $(meds/deps)

.PHONY: clean
clean:
	@$(RM) $(deps) $(meds/deps)
	$(RM) $(objs) $(target) $(meds/objs) $(meds/lex) $(meds/yacc)
