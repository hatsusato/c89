#!/usr/bin/make -f

LEX := flex
YACC := bison
target := main.out
lex_prefix := src/lexer
yacc_prefix := src/parser
files := ast list main node parser pool pretty print register scanner set sexp str utility vector

builddir := $(CURDIR)/build

ldflags =
cflags = -Wall -Wextra -ansi -pedantic -Iinclude
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
lflags := --header-file=$(lex_prefix).h --outfile=$(lex_prefix).c
yflags := -d -b $(yacc_prefix)
lex_intermeds := $(addprefix $(lex_prefix),.c .h)
yacc_intermeds := $(addprefix $(yacc_prefix),.tab.c .tab.h)
intermeds := $(lex_intermeds) $(yacc_intermeds)
srcs := $(files:%=src/%.c) $(filter %.c,$(intermeds))
objs := $(srcs:%.c=$(builddir)/%.o)
deps := $(objs:%.o=%.d)

ifeq (,$(wildcard .develop))
cflags += -O3 -DNDEBUG
else
cflags += -O0 -g
endif

.SUFFIXES:

.PHONY: all
all: $(target)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

$(lex_intermeds): $(lex_prefix).l $(yacc_prefix).tab.h
	$(LEX) $(lflags) $<

$(yacc_intermeds): $(yacc_prefix).y
	$(YACC) $(yflags) $<

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

-include $(deps)

.PHONY: clean distclean
clean:
	$(RM) -r $(builddir) $(intermeds)
distclean: clean
	$(RM) $(target)
