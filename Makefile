#!/usr/bin/make -f

target = main.out
ldflags =
cflags = -Wall -Wextra -ansi -pedantic
release_cflags = -O3 -DNDEBUG
debug_cflags = -g
srcs = src/main.c
objs = $(srcs:src/%.c=obj/%.o)

.PHONY: all release debug
all: release
release debug: $(target)
release: cflags += $(release_cflags)
debug: cflags += $(debug_cflags)

$(target): $(objs)
	$(CC) $(ldflags) $^ -o $@

$(objs): obj/%.o: src/%.c | obj
	$(CC) $(cflags) -c $< -o $@

obj:
	mkdir -p $@

.PHONY: clean distclean
clean:
	$(RM) -r obj
distclean: clean
	$(RM) $(target)
