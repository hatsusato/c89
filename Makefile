#!/usr/bin/make -f

LEX = flex
YACC = bison
target = main.out
ldflags =
cflags = -Wall -Wextra -ansi -pedantic
release_cflags = -O3 -DNDEBUG
debug_cflags = -g
lflags = -t
yflags = -d -b $(yacc_pre)
lex_pre = src/lexer
lex_src = $(lex_pre).l
lex_med = $(lex_pre).c
lex_obj = $(lex_pre:src/%=obj/%).o
yacc_pre = src/parser
yacc_src = $(yacc_pre).y
yacc_med = $(yacc_pre).tab.c $(yacc_pre).tab.h
yacc_obj = $(yacc_pre:src/%=obj/%).tab.o
srcs = src/main.c
objs = $(srcs:src/%.c=obj/%.o) $(lex_obj) $(yacc_obj)
deps = $(objs:%.o=%.d)
meds = $(lex_med) $(yacc_med)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

.INTERMEDIATE: $(lex_med)
$(lex_med): $(lex_src) $(yacc_med)
	$(LEX) $(lflags) $< > $@
$(lex_obj): cflags += -Wno-unused-function

.INTERMEDIATE: $(yacc_med)
$(yacc_med): $(yacc_src)
	$(YACC) $(yflags) $<

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

$(deps): obj/%.d: src/%.c | obj
	$(CC) -MG -MM -MP $< -MF $@

-include $(deps)

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj $(meds)
distclean: clean
	$(RM) $(target)
