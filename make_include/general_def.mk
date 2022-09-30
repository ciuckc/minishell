NAME := minishell

SRC_DIR := src

OBJ_DIR := obj

CC := gcc

FLAGS := -Wall -Wextra -Werror

INCLUDE := -Iinclude

LDFLAGS = -L $(shell brew --prefix readline)/lib -lreadline

CFLAGS = -I $(shell brew --prefix readline)/include

MAIN_SRC := $(SRC_DIR)/minishell.c

MAIN_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(MAIN_SRC:.c=.o)))