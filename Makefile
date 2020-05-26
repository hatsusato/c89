#!/usr/bin/make -f

LEX = flex
YACC = bison
target = main.out
ldflags =
cflags = -Wall -Wextra -ansi -pedantic
cflags += -MMD -MP -MT $@
release_cflags = -O3 -DNDEBUG
debug_cflags = -g
lex_prefix = src/lexer
lex_intermeds = $(addprefix $(lex_prefix),.c .h)
yacc_prefix = src/parser
yacc_intermeds = $(addprefix $(yacc_prefix),.tab.c .tab.h)
intermeds = $(lex_intermeds) $(yacc_intermeds)
files = main.c vector.c
srcs = $(filter %.c,$(intermeds)) $(addprefix src/,$(files))
objs = $(srcs:src/%.c=obj/%.o)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

$(lex_intermeds): $(lex_prefix).l $(yacc_prefix).tab.h
	$(LEX) --header-file=$(lex_prefix).h --outfile=$(lex_prefix).c $<

$(yacc_intermeds): $(yacc_prefix).y
	$(YACC) -d -b $(yacc_prefix) $<

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

-include $(objs:%.o=%.d)

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj $(intermeds)
distclean: clean
	$(RM) $(target)
