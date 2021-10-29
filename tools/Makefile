CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -O2
PROGRAMS := vtxdis

all: $(PROGRAMS)
	$(MAKE) -C ZAPD
	$(MAKE) -C fado
	$(MAKE) -C buildtools
	$(MAKE) -C z64compress

clean:
	$(RM) $(PROGRAMS)
	$(MAKE) -C ZAPD clean
	$(MAKE) -C fado clean
	$(MAKE) -C buildtools clean
	$(MAKE) -C z64compress clean

vtxdis_SOURCES	   := vtxdis.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
