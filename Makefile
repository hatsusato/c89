#!/usr/bin/make -f

LEX = flex
YACC = bison
target = main.out
ldflags =
cflags = -Wall -Wextra -ansi -pedantic
cflags += -MMD -MP -MT $@
release_cflags = -O3 -DNDEBUG
debug_cflags = -g
yflags = -d -b $(yacc_pre)
yacc_pre = src/parser
yacc_src = $(yacc_pre).y
yacc_med = $(yacc_pre).tab.c $(yacc_pre).tab.h
yacc_obj = $(yacc_pre:src/%=obj/%).tab.o
srcs = src/main.c src/vector.c
objs = $(srcs:src/%.c=obj/%.o) $(lex_obj) $(yacc_obj)
meds = $(lex_med) $(yacc_med)
lex_prefix = src/lexer
lex_intermeds = $(addprefix $(lex_prefix),.c .h)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

$(lex_intermeds): $(lex_prefix).l $(yacc_prefix).tab.h
	$(LEX) --header-file=$(lex_prefix).h --outfile=$(lex_prefix).c $<

.INTERMEDIATE: $(yacc_med)
$(yacc_med): $(yacc_src)
	$(YACC) $(yflags) $<

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

-include $(objs:%.o=%.d)

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj $(meds)
distclean: clean
	$(RM) $(target)
