CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -g -Os
PROGRAMS := mkdmadata mkldscript reloc_prereq

ifeq ($(shell command -v clang >/dev/null 2>&1; echo $$?),0)
  CC := clang
else
  CC := gcc
endif

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)

mkdmadata_SOURCES    := mkdmadata.c spec.c util.c
mkldscript_SOURCES   := mkldscript.c spec.c util.c
reloc_prereq_SOURCES := reloc_prereq.c spec.c util.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
