# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
INCLUDES = -Iinclude
LDFLAGS = -lm -lncurses

# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Source files, object files, and target
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
TARGET = snake
TARGET_BIN = $(BINDIR)/$(TARGET)

# Phony targets
.PHONY: all help clean lint format run

# Default target: build the executable
all: $(TARGET_BIN)

# Link object files and create the executable
$(TARGET_BIN): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_BIN) $(OBJS) $(LDFLAGS)

# Compile source files and create object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Help target: display help information
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default target)"
	@echo "  run     - Build and run the project"
	@echo "  clean   - Remove build artifacts (object files and executable)"
	@echo "  lint    - Run clang-tidy on source files for static analysis"
	@echo "  format  - Format source and header files using clang-format"
	@echo "  help    - Display this help message"

# Run target: build and run the executable
run: all
	./$(TARGET_BIN)

# Clean target: remove build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Lint target: run clang-tidy for static analysis
lint:
	clang-tidy $(SRCS) -- $(INCLUDES)

# Format target: format source and header files using clang-format
format:
	clang-format -i $(SRCS) $(wildcard include/*.h)
