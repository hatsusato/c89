#!/usr/bin/make -f

LEX := flex
YACC := bison
target := main.out
lex_prefix := src/lexer
yacc_prefix := src/parser
files := ast list main parser pretty print result scanner set sexp string utility vector

ldflags =
cflags = -Wall -Wextra -ansi -pedantic
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
release_cflags := -O3 -DNDEBUG
debug_cflags := -g
lflags := --header-file=$(lex_prefix).h --outfile=$(lex_prefix).c
yflags := -d -b $(yacc_prefix)
lex_intermeds := $(addprefix $(lex_prefix),.c .h)
yacc_intermeds := $(addprefix $(yacc_prefix),.tab.c .tab.h)
intermeds := $(lex_intermeds) $(yacc_intermeds)
srcs := $(files:%=src/%.c) $(filter %.c,$(intermeds))
objs := $(srcs:src/%.c=obj/%.o)
deps := $(objs:%.o=%.d)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

.SUFFIXES:

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

$(lex_intermeds): $(lex_prefix).l $(yacc_prefix).tab.h
	$(LEX) $(lflags) $<

$(yacc_intermeds): $(yacc_prefix).y
	$(YACC) $(yflags) $<

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

obj/parser.tab.d: src/lexer.h
$(deps): obj/%.d: src/%.c | obj
	$(CC) $(dflags) $<

-include $(deps)

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj $(intermeds)
distclean: clean
	$(RM) $(target)
