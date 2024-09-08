# Compiler settings - Can change to g++-11 if using a specific version
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

# Target executable name
TARGET = snake breakout

# Automatically finds all .cc files in the current directory
SOURCES = $(wildcard *.cc)

# Object files have the same names as the source files, but with .o extension
OBJECTS = $(SOURCES:%.cc=temps/%.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out $(TARGET:%=temps/%.o),$^) temps/$@.o -lncurses

# Compiling
temps/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I../inc

# Clean
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
