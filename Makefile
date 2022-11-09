include make_include/sources_def.mk make_include/utilities.mk

all: $(NAME)

#	Compile objects into exec

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): | $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

#	Create object files

$(NAME_LIBFT):
	$(MAKE) bonus -C $(DIR_LIBFT)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(FLAGS) $(INCLUDE) $(INCLUDE) $(CFLAGS) -c $< -o $@

#	Template for adding new object file from src files
#
#	$(OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c
#		$(CC) $(FLAGS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXEC_UTILSDIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	$(RM) -r $(NAME) 
	$(RM) -r $(NAME_LIBFT)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re