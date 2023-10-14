CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -g -Os
PROGRAMS := elf2rom makeromfs mkldscript reloc_prereq yaz0 makeyar

ifeq ($(shell command -v clang >/dev/null 2>&1; echo $$?),0)
  CC := clang
else
  CC := gcc
endif

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)

elf2rom_SOURCES      := elf2rom.c elf32.c n64chksum.c util.c
makeromfs_SOURCES    := makeromfs.c n64chksum.c util.c
mkldscript_SOURCES   := mkldscript.c spec.c util.c
reloc_prereq_SOURCES := reloc_prereq.c spec.c util.c
yaz0_SOURCES         := yaz0tool.c yaz0.c util.c
makeyar_SOURCES      := makeyar.c elf32.c yaz0.c util.c

define COMPILE =
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
