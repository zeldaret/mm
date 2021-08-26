CXXFLAGS = -Wall -O2 -g -std=c++17
OBJ = Main.o TextureExporter.o RoomExporter.o CollisionExporter.o
LIB = ExporterTest.a

CPPFLAGS-$(MT) += -DCONFIG_MT
CPPFLAGS += $(CPPFLAGS-y)

.PHONY: all
all: $(LIB)

.PHONY: clean
clean:
	rm -f $(OBJ) $(LIB)

.INTERMEDIATE: $(OBJ)

$(OBJ): Main.cpp TextureExporter.cpp RoomExporter.cpp CollisionExporter.cpp

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(COMPILE.c) $(OUTPUT_OPTION) $(CXXFLAGS) $< -I ./ -I ../ZAPD -I ../ZAPDUtils -I ../lib/tinyxml2
