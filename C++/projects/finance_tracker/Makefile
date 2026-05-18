# Makefile — CLI Finance Tracker

CXX      := clang++
CXXFLAGS := -Wall -Wextra -Wpedantic -std=c++17
TARGET   := finance_tracker
SOURCES  := main.cpp

# Default target — runs when you type 'make' with no arguments
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 'make clean' removes the compiled binary
clean:
	rm -f $(TARGET)

# .PHONY tells make these targets don't correspond to actual files
.PHONY: all clean
