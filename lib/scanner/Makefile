#!/usr/bin/make -f

builddir := $(BUILD_DIR)
target := $(builddir)/lib/scanner.a
outdir := $(builddir)/lib/scanner

cflags := $(CFLAGS) -I$(outdir) -I.
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
lflags := --header-file=$(outdir)/lexer.h --outfile=$(outdir)/lexer.c
yflags := -d -b $(outdir)/parser

lex := $(addprefix $(outdir)/lexer.,c h)
yacc := $(addprefix $(outdir)/parser.tab.,c h)
srcs != git ls-files *.c
objs := $(srcs:%.c=$(outdir)/%.o)
deps := $(objs:%.o=%.d)
meds/srcs := $(filter %.c,$(lex) $(yacc))
meds/objs := $(meds/srcs:%.c=%.o)
meds/deps := $(meds/objs:%.o=%.d)
cleanobjs := $(objs) $(target) $(meds/objs)
cleandeps := $(deps) $(lex) $(yacc) $(meds/deps)

.SUFFIXES:

.PHONY: build
build: $(target)

$(target): $(objs) $(meds/objs)
	$(AR) rcs $@ $^

$(objs): $(outdir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(outdir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

$(lex): lexer.l $(outdir)/parser.tab.h
	@mkdir -p $(@D)
	flex $(lflags) $<

$(yacc): parser.y
	@mkdir -p $(@D)
	bison $(yflags) $<

$(meds/objs): %.o: %.c
	$(CC) $(cflags) -c $< -o $@

$(meds/deps): %.d: %.c
	$(CC) $(dflags) $<

-include $(deps) $(meds/deps)

.PHONY: clean
clean:
	$(RM) $(cleanobjs)
	$(RM) $(cleandeps)
