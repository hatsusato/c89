#!/usr/bin/make -f

builddir := build
target := $(builddir)/main.out
develop-mode := $(if $(wildcard .develop),ON,)

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
scanner/hdrs := $(scanner/lex/hdr) $(scanner/yacc/hdr)
scanner/srcs := $(scanner/lex/src) $(scanner/yacc/src)
scanner/objs := $(scanner/srcs:%.c=%.o)
scanner/deps := $(scanner/objs:%.o=%.d)
scanner/outs := $(filter $(scanner/outdir)/%,$(objs) $(deps))
scanner/outs := $(scanner/outs) $(scanner/objs) $(scanner/deps)

ldflags =
cflags = -Wall -Wextra -ansi -pedantic -Iinclude
dflags = $(cflags) -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
lflags := --header-file=$(scanner/lex/hdr) --outfile=$(scanner/lex/src)
yflags := -d -b $(scanner/yacc/prefix)

ifeq (ON,$(develop-mode))
cflags += -O0 -g
else
cflags += -O3 -DNDEBUG
endif

.SUFFIXES:

.PHONY: all
all: $(target)

$(target): $(objs) $(scanner/objs)
	$(CC) $(ldflags) $^ -o $@

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(scanner/lex): $(scanner/lex/file)
	@mkdir -p $(@D)
	flex $(lflags) $<

$(scanner/yacc): $(scanner/yacc/file)
	@mkdir -p $(@D)
	bison $(yflags) $<

$(scanner/objs): %.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(scanner/outs): cflags += -I$(@D)
$(scanner/outs): $(scanner/hdrs)

ifeq (ON,$(develop-mode))
$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

$(scanner/deps): %.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

-include $(deps) $(scanner/deps)
endif

.PHONY: clean
clean:
	@$(RM) $(deps) $(scanner/deps)
	$(RM) $(objs) $(target)
	$(RM) $(scanner/objs) $(scanner/lex) $(scanner/yacc)
