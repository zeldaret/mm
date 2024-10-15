CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -O2
PROGRAMS := vtxdis

all: $(PROGRAMS)
	$(MAKE) -C ZAPD
	$(MAKE) -C fado
	$(MAKE) -C buildtools
	$(MAKE) -C audio

clean:
	$(RM) $(PROGRAMS)
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
