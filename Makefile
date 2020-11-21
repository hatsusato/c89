#!/usr/bin/make -f

target := main.out
builddir := $(CURDIR)/build
includedir := $(CURDIR)/include
libs/dir != find lib/ -mindepth 1 -type d
libs := $(libs/dir:%=$(builddir)/%.a)

ldflags = -L$(builddir)/lib $(libs/dir:lib/%=-l:%.a)
cflags = -Wall -Wextra -ansi -pedantic -I$(includedir)
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)
srcs != git ls-files src/*.c
objs := $(srcs:%.c=$(builddir)/%.o)
deps := $(objs:%.o=%.d)
builds := $(libs/dir:%=build/%)
cleans := $(libs/dir:%=clean/%)

ifeq (,$(wildcard .develop))
cflags += -O3 -DNDEBUG
else
cflags += -O0 -g
endif

export BUILD_DIR = $(builddir)
export CFLAGS = $(cflags)

.SUFFIXES:

.PHONY: build $(builds)
build: $(target)
$(builds): build/%: $(builddir)/%.a

$(target): $(objs) $(libs)
	$(CC) $(ldflags) $^ -o $@

$(libs): $(builddir)/%.a:
	$(MAKE) -C $* build

$(objs): $(builddir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(builddir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

-include $(deps)

.PHONY: clean $(cleans)
clean: $(cleans)
	$(RM) $(objs) $(deps) $(target)
$(cleans): clean/%:
	$(MAKE) -C $* clean
