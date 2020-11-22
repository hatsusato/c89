#!/usr/bin/make -f

builddir := $(BUILD_DIR)
target := $(builddir)/lib/set.a
outdir := $(builddir)/lib/set

cflags := $(CFLAGS) -I.
dflags = -MF $@ -MG -MM -MP -MT $(@:%.d=%.o)

srcs != git ls-files *.c
objs := $(srcs:%.c=$(outdir)/%.o)
deps := $(objs:%.o=%.d)
cleanobjs := $(objs) $(target)
cleandeps := $(deps)

.SUFFIXES:

.PHONY: build
build: $(target)

$(target): $(objs)
	$(AR) rcs $@ $^

$(objs): $(outdir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(cflags) -c $< -o $@

$(deps): $(outdir)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(dflags) $<

-include $(deps)

.PHONY: clean
clean:
	$(RM) $(cleanobjs)
	$(RM) $(cleandeps)
