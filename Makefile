include utilities.mk

all: $(NAME)

$(NAME): $(NAME_UTILS)
	$(CC) $(FLAGS) $(INCLUDE) $(SRC_DIR)/$(addsuffix .c,$(NAME)) $(NAME_UTILS) -o $(NAME)

$(NAME_UTILS):
	$(MAKE) -C $(DIR_GNL)
	$(MAKE) -C $(DIR_PRINTF)
	$(MAKE) -C $(DIR_LIBFT)

clean:
	$(MAKE) clean -C $(DIR_GNL)
	$(MAKE) clean -C $(DIR_PRINTF)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	$(RM) -f $(NAME) $(NAME_UTILS)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re