CC = gcc
CFLAGS = -Wall -Wextra -O2 -I include
SRC_DIR = src
OBJ_DIR = obj
OUT_DIR = output

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(OUT_DIR)/turbofire

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR) $(OUT_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

.PHONY: all dirs run clean
