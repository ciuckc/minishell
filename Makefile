include make_include/sources_def.mk make_include/utilities.mk

all: $(NAME)

#	Compile objects into exec

$(OBJ_DIR):
	mkdir -p $@

$(OBJ) : | $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

#	Create object files for libs

$(NAME_HASH):
	$(MAKE) -C $(DIR_HASH)

$(DIR_LIBFT):
	git submodule init
	git submodule update

$(NAME_LIBFT): $(DIR_LIBFT)
	$(MAKE) bonus -C $(DIR_LIBFT)

#	Template for adding new object file from src files
#
#	$(OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c
#		$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SIG_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ENV_INIT_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXPANSION_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(FREE_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

test: $(NAME)
	gcc -Wall -Wextra -Werror $(NAME_LIBFT) test.c

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(DIR_LIBFT)
	$(MAKE) clean -C $(DIR_HASH)

fclean: clean
	$(RM) -r $(NAME) 
	$(RM) -r $(NAME_LIBFT)
	$(RM) -r $(NAME_HASH)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re