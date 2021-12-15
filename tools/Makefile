CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -O2
PROGRAMS := vtxdis

all: $(PROGRAMS)
	$(MAKE) -C ZAPD
	$(MAKE) -C buildtools
# CFLAGS is needed for platforms without -march and -mtune available; you can remove it to use the defaults from z64compress
	$(MAKE) -C z64compress CFLAGS="-DNDEBUG -s -Os -flto -Wall -Wextra"

clean:
	$(RM) $(PROGRAMS)
	$(MAKE) -C ZAPD clean
	$(MAKE) -C buildtools clean
	$(MAKE) -C z64compress clean

vtxdis_SOURCES	   := vtxdis.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
