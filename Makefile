#!/usr/bin/make -f

target := main.out
files := ast list main node pool pretty print set sexp str utility vector
builddir := $(CURDIR)/build
includedir := $(CURDIR)/include

ldflags = -L$(builddir)/lib -l:scanner.a
cflags = -Wall -Wextra -ansi -pedantic -I$(includedir)
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
srcs := $(files:%=src/%.c)
objs := $(srcs:%.c=$(builddir)/%.o)
deps := $(objs:%.o=%.d)

ifeq (,$(wildcard .develop))
cflags += -O3 -DNDEBUG
else
cflags += -O0 -g
endif

export BUILD_DIR = $(builddir)
export CFLAGS = $(cflags)

.SUFFIXES:

.PHONY: all
all: $(target)

$(target): $(objs) $(builddir)/lib/scanner.a
	$(CC) $(ldflags) $^ -o $@

$(builddir)/lib/scanner.a:
	$(MAKE) -C lib/scanner build

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

-include $(deps)

.PHONY: clean distclean
clean:
	$(RM) -r $(builddir) $(intermeds) $(target)
	$(MAKE) -C lib/scanner clean
