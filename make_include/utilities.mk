include make_include/general_def.mk

UTILS = $(SRC_DIR)/utils

#LIBFT

DIR_LIBFT = $(UTILS)/libft

NAME_LIBFT = $(DIR_LIBFT)/libft.a

OBJ += $(NAME_LIBFT)

#HASHMAP

DIR_HASH = $(UTILS)/hashmap

NAME_HASH = $(DIR_HASH)/hashmap.a

OBJ += $(NAME_HASH)