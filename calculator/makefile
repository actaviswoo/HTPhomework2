CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TARGET_DIR = target

all: clean main

main: $(TARGET_DIR)/main
	./$<

clean:
	rm -rf $(TARGET_DIR)/*

$(TARGET_DIR)/main: src/main.cc | $(TARGET_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

.PHONY: all clean main