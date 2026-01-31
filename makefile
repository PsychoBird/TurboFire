CC = gcc
CFLAGS = -Wall -Wextra -O2 -I include
SRC_DIR = src
OBJ_DIR = obj
OUT_DIR = output

# Test Configuration
TEST_DIR = test
TEST_OUT_DIR = $(OUT_DIR)/tests

# Source & Object definitions
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Main Target
TARGET = $(OUT_DIR)/turbofire

# Test Sources & Binaries
# Finds all .c files in test/ and converts them to targets in output/tests/
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_OUT_DIR)/%, $(TEST_SRCS))

# Library Objects: All objects EXCEPT the main program entry point
# We assume turbofire.c contains your main() function. 
# We filter it out so we can link tests against ranks.o without double main() errors.
MAIN_OBJ = $(OBJ_DIR)/turbofire.o
LIB_OBJS = $(filter-out $(MAIN_OBJ), $(OBJS))

# --- TARGETS ---

# 'all' now builds the main app AND all tests
all: dirs $(TARGET) tests

dirs:
	@mkdir -p $(OBJ_DIR) $(OUT_DIR) $(TEST_OUT_DIR)

# Link the main executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- TEST RULES ---

# Target to just build tests
tests: $(TEST_BINS)

# Compile each test file
# Note: We link against $(LIB_OBJS) (ranks.o, etc) but NOT turbofire.o
$(TEST_OUT_DIR)/%: $(TEST_DIR)/%.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $< $(LIB_OBJS) -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

.PHONY: all dirs run clean tests
