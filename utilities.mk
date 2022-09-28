include general_def.mk

UTILS = $(SRC_DIR)/utils

#PRINTF

DIR_PRINTF = $(UTILS)/ft_printf

NAME_PRINTF = $(DIR_PRINTF)/libftprintf.a

#GNL

DIR_GNL = $(UTILS)/get_next_line

NAME_GNL = $(DIR_GNL)/get_next_line.a

#LIBFT

DIR_LIBFT = $(UTILS)/libft

NAME_LIBFT = $(DIR_LIBFT)/libft.a

NAME_UTILS := $(NAME_GNL) $(NAME_LIBFT) $(NAME_PRINTF)