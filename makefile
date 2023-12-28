# Compiler settings - Can change to g++-11 if using a specific version
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Target executable name
TARGET = snake breakout

# Automatically finds all .cpp files in the current directory
SOURCES = $(wildcard *.cc)

# Object files have the same names as the source files, but with .o extension
OBJECTS = $(SOURCES:%.cc=%.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lncurses

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
