CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -O2
PROGRAMS := vtxdis

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  DETECTED_OS=linux
else ifeq ($(UNAME_S),Darwin)
  DETECTED_OS=macos
else
  $(error Unsupported OS: $(UNAME_S))
endif

IDO_RECOMP_VERSION := v1.2
IDO_RECOMP_5_3_DIR := ido_recomp/$(DETECTED_OS)/5.3
IDO_RECOMP_7_1_DIR := ido_recomp/$(DETECTED_OS)/7.1

all: $(PROGRAMS) $(IDO_RECOMP_5_3_DIR) $(IDO_RECOMP_7_1_DIR)
	$(MAKE) -C ZAPD
	$(MAKE) -C fado
	$(MAKE) -C buildtools
	$(MAKE) -C audio

clean:
	$(RM) $(PROGRAMS)
	$(RM) -r ido_recomp
	$(MAKE) -C ZAPD clean
	$(MAKE) -C fado clean
	$(MAKE) -C buildtools clean
	$(MAKE) -C audio clean

distclean: clean
	$(MAKE) -C audio distclean

.PHONY: all clean distclean

vtxdis_SOURCES	   := vtxdis.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))

$(IDO_RECOMP_5_3_DIR):
	mkdir -p $@
	curl -sL https://github.com/decompals/ido-static-recomp/releases/download/$(IDO_RECOMP_VERSION)/ido-5.3-recomp-$(DETECTED_OS).tar.gz | tar xz -C $@

$(IDO_RECOMP_7_1_DIR):
	mkdir -p $@
	curl -sL https://github.com/decompals/ido-static-recomp/releases/download/$(IDO_RECOMP_VERSION)/ido-7.1-recomp-$(DETECTED_OS).tar.gz | tar xz -C $@
