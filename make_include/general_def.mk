NAME := minishell

SRC_DIR := src

OBJ_DIR := obj

CC := gcc

FLAGS := -Wall -Wextra -Werror -g  # -fsanitize=address

INCLUDE := -I include -I src/utils/hashmap

LDFLAGS = -L $(shell brew --prefix readline)/lib -lreadline

CFLAGS = -I $(shell brew --prefix readline)/include
