DEBUG       ?= 0
LLD         ?= 1
ASAN        ?= 0

ELF         := fado.elf

CC          := clang
INC         := -I include -I lib
WARNINGS    := -Wall -Wextra -Wpedantic -Wshadow -Werror=implicit-function-declaration -Wvla -Wno-unused-function
CFLAGS      := -std=c11
LDFLAGS     := 

ifeq ($(DEBUG),0)
  OPTFLAGS  := -O2
  CFLAGS    += -Werror
else
  OPTFLAGS  := -O0 -g3 -DDEBUG_ON
endif

ifneq ($(ASAN),0)
  CFLAGS    += -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined
endif

ifneq ($(LLD),0)
  LDFLAGS   += -fuse-ld=lld
endif

SRC_DIRS    := $(shell find src -type d)
C_FILES     := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
H_FILES     := $(foreach dir,$(INC),$(wildcard $(dir)/*.h))
O_FILES     := $(foreach f,$(C_FILES:.c=.o),build/$f)

LIB_DIRS    := $(shell find lib -type d)
# exclude test file since we don't want it
C_LIB_FILES := $(filter-out lib/vc_vector/vc_vector_test.c, $(foreach dir,$(LIB_DIRS),$(wildcard $(dir)/*.c)))
O_LIB_FILES := $(foreach f,$(C_LIB_FILES:.c=.o),build/$f)

# Main targets
all: $(ELF)

clean:
	$(RM) -r build $(ELF)

format:
	clang-format-11 -i $(C_FILES) $(H_FILES)

.PHONY: all clean format

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS),build/$(dir)) $(foreach dir,$(LIB_DIRS),build/$(dir)))

$(ELF): $(O_FILES) $(O_LIB_FILES)
	$(CC) $(INC) $(WARNINGS) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) -o $@ $^

build/%.o: %.c $(H_FILES)
	$(CC) -c $(INC) $(WARNINGS) $(CFLAGS) $(OPTFLAGS) -o $@ $<

build/lib/%.o: lib/%.c
	$(CC) -c $(INC) $(WARNINGS) $(CFLAGS) $(OPTFLAGS) -o $@ $<
