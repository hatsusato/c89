#!/usr/bin/make -f

LEX = flex
target = main.out
ldflags =
cflags = -Wall -Wextra -ansi -pedantic
release_cflags = -O3 -DNDEBUG
debug_cflags = -g
lflags = -t
lex_pre = src/lexer
lex_src = $(lex_pre).l
lex_med = $(lex_pre).c
lex_obj = $(lex_pre:src/%=obj/%).o
srcs = src/main.c
objs = $(srcs:src/%.c=obj/%.o) $(lex_obj)
deps = $(objs:%.o=%.d)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

.INTERMEDIATE: $(lex_med)
$(lex_med): $(lex_src)
	$(LEX) $(lflags) $< > $@
$(lex_obj): cflags += -Wno-unused-function

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

$(deps): obj/%.d: src/%.c | obj
	$(CC) -MG -MM -MP $< -MF $@

-include $(deps)

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj
distclean: clean
	$(RM) $(target)
