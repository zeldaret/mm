OPTIMIZATION_ON ?= 1
ASAN ?= 0
DEPRECATION_ON ?= 1
DEBUG ?= 0
COPYCHECK_ARGS ?= 

CXX := g++
INC := -I ZAPD -I lib/elfio -I lib/libgfxd -I lib/tinyxml2 -I ZAPDUtils
CXXFLAGS := -fpic -std=c++17 -Wall -Wextra -fno-omit-frame-pointer
OPTFLAGS :=

ifneq ($(DEBUG),0)
  OPTIMIZATION_ON = 0
  DEPRECATION_OFF = 1
  COPYCHECK_ARGS += --devel
  DEPRECATION_ON = 0
else
  CXXFLAGS += -Werror
endif

ifeq ($(OPTIMIZATION_ON),0)
  OPTFLAGS := -O0
else
  OPTFLAGS := -O2 -march=native -mtune=native
endif

ifneq ($(ASAN),0)
  CXXFLAGS += -fsanitize=address
endif
ifneq ($(DEPRECATION_ON),0)
  CXXFLAGS += -DDEPRECATION_ON
endif
# CXXFLAGS += -DTEXTURE_DEBUG

LDFLAGS := -lstdc++ -lm -ldl -lpng

UNAME := $(shell uname)
ifneq ($(UNAME), Darwin)
    LDFLAGS += -Wl,-export-dynamic -lstdc++fs
endif

SRC_DIRS := ZAPD ZAPD/ZRoom ZAPD/ZRoom/Commands ZAPD/Overlays ZAPD/HighLevel ZAPD/Utils

ZAPD_CPP_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
ZAPD_H_FILES   := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))

CPP_FILES += $(ZAPD_CPP_FILES) lib/tinyxml2/tinyxml2.cpp
O_FILES   := $(CPP_FILES:.cpp=.o)

all: ZAPD.out copycheck

genbuildinfo:
	python3 ZAPD/genbuildinfo.py $(COPYCHECK_ARGS)

copycheck: ZAPD.out
	python3 copycheck.py

clean:
	rm -f $(O_FILES) ZAPD.out
	$(MAKE) -C lib/libgfxd clean

rebuild: clean all

format:
	clang-format-11 -i $(ZAPD_CPP_FILES) $(ZAPD_H_FILES)

.PHONY: all genbuildinfo copycheck clean rebuild format

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INC) -c $< -o $@

ZAPD/Main.o: genbuildinfo ZAPD/Main.cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INC) -c ZAPD/Main.cpp -o $@

lib/libgfxd/libgfxd.a:
	$(MAKE) -C lib/libgfxd

ExporterTest/ExporterTest.a:
	$(MAKE) -C ExporterTest

ZAPDUtils/ZAPDUtils.a:
	$(MAKE) -C ZAPDUtils

ZAPD.out: $(O_FILES) lib/libgfxd/libgfxd.a ExporterTest/ExporterTest.a ZAPDUtils/ZAPDUtils.a
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INC) $(O_FILES) lib/libgfxd/libgfxd.a ZAPDUtils/ZAPDUtils.a -Wl,--whole-archive ExporterTest/ExporterTest.a -Wl,--no-whole-archive -o $@ $(FS_INC) $(LDFLAGS)
