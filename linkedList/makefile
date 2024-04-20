CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TARGET_DIR = target
GTEST_LIB = -lgtest -fsanitize=address

all: clean main test

clean:
	rm -rf $(TARGET_DIR)/*

main: $(TARGET_DIR)/main
	./$<

test: clean $(TARGET_DIR)/Tests
	./$(TARGET_DIR)/Tests

$(TARGET_DIR)/Tests: Tests/Tests.cc
	$(CC) $(CFLAGS) $^ $(GTEST_LIB) -o $@

$(TARGET_DIR)/main: src/main.cc | $(TARGET_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

.PHONY: all clean run test