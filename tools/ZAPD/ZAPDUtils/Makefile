CXXFLAGS = -Wall -O2 -g -std=c++17
OBJ = Utils/BinaryWriter.o Utils/MemoryStream.o
LIB = ZAPDUtils.a

CPPFLAGS-$(MT) += -DCONFIG_MT
CPPFLAGS += $(CPPFLAGS-y)

.PHONY: all
all: $(LIB)

.PHONY: clean
clean:
	rm -f $(OBJ) $(LIB)

.INTERMEDIATE: $(OBJ)

$(OBJ): Utils/BinaryReader.cpp Utils/BinaryWriter.cpp Utils/MemoryStream.cpp

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(COMPILE.c) $(OUTPUT_OPTION) $(CXXFLAGS) $< -I ./ -I ../ZAPD -I ../lib/tinyxml2
