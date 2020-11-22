#!/usr/bin/make -f

builddir := build
target := $(builddir)/main.out

srcs != git ls-files src/
srcs := $(filter %.c,$(srcs))
objs := $(srcs:%.c=$(builddir)/%.o)
deps := $(objs:%.o=%.d)

scanner/srcdir := src/scanner
scanner/outdir := $(builddir)/$(scanner/srcdir)
scanner/lex/file := $(scanner/srcdir)/lexer.l
scanner/lex/prefix := $(scanner/outdir)/lexer
scanner/lex/hdr := $(scanner/lex/prefix).h
scanner/lex/src := $(scanner/lex/prefix).c
scanner/lex := $(scanner/lex/hdr) $(scanner/lex/src)
scanner/yacc/file := $(scanner/srcdir)/parser.y
scanner/yacc/prefix := $(scanner/outdir)/parser
scanner/yacc/hdr := $(scanner/yacc/prefix).tab.h
scanner/yacc/src := $(scanner/yacc/prefix).tab.c
scanner/yacc := $(scanner/yacc/hdr) $(scanner/yacc/src)
scanner/srcs := $(scanner/lex/src) $(scanner/yacc/src)
scanner/objs := $(scanner/srcs:%.c=%.o)
scanner/deps := $(scanner/objs:%.o=%.d)
scanner/outs := $(objs) $(deps) $(scanner/objs) $(scanner/deps)
scanner/outs := $(filter $(scanner/outdir)/%,$(scanner/outs))

ldflags =
cflags = -Wall -Wextra -ansi -pedantic -Iinclude -I$(<D:$(builddir)/%=%)
dflags = $(cflags) -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
lflags := --header-file=$(scanner/lex/hdr) --outfile=$(scanner/lex/src)
yflags := -d -b $(scanner/yacc/prefix)

ifeq (,$(wildcard .develop))
cflags += -O3 -DNDEBUG
else
cflags += -O0 -g
endif

.SUFFIXES:

.PHONY: all
all: $(target)

$(target): $(objs) $(scanner/objs)
	$(CC) $(ldflags) $^ -o $@

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

$(scanner/outs): cflags += -I$(@D)

$(scanner/lex): $(scanner/lex/file)
	@mkdir -p $(@D)
	flex $(lflags) $<

$(scanner/yacc): $(scanner/yacc/file)
	@mkdir -p $(@D)
	bison $(yflags) $<

$(scanner/objs): %.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(scanner/deps): %.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

$(scanner/yacc/prefix).tab.d: $(scanner/lex/prefix).d

-include $(deps) $(scanner/deps)

.PHONY: clean
clean:
	@$(RM) $(deps) $(scanner/deps)
	$(RM) $(objs) $(target)
	$(RM) $(scanner/objs) $(scanner/lex) $(scanner/yacc)
