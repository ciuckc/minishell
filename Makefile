include make_include/sources_def.mk make_include/utilities.mk

all: $(NAME)

#	Compile objects into exec

$(OBJ_DIR):
	mkdir -p $@

$(OBJ) : | $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS)  -g $(CFLAGS) $(OBJ) -o $(NAME)

#	Create object files for libs

$(NAME_LIBFT):
	$(MAKE) bonus -C $(DIR_LIBFT)

$(NAME_HASH):
	$(MAKE) -C $(DIR_HASH)

#	Template for adding new object file from src files
#
#	$(OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c
#		$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(FLAGS) $(INCLUDE) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXPANSION_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(FREE_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

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