# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Target executable
TARGET = crypto-suite

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compile .c → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Convenience target to run program
run: $(TARGET)
	./$(TARGET)

