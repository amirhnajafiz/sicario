# compiler
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -O2

# project
NAME = sicario
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

CFLAGS += -I$(INC_DIR)

# files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# default rule
all: $(NAME)

# link
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# clean
clean:
	rm -rf $(BUILD_DIR) $(NAME)

# rebuild
re: clean all

.PHONY: all clean re

