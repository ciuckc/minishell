include make_include/general_def.mk

#	Template for adding different directories with source file
#	
#	#	EXAMPLE
#	EXAMPLE_DIR = $(SRC_DIR)/example
#	EXAMPLE_SRC = source1.c source2.c source3.c ...
#	EXAMPLE_OBJ = $(addprefix $(OBJ_DIR)/,$(EXAMPLE_SRC:.c=.o))
#	OBJ += $(EXAMPLE_OBJ)

#	EXPANSION

EXPANSION_DIR = $(SRC_DIR)/expansion

EXPANSION_SRC = expand_variables.c expand_var_in_str.c expanded_var_len.c

EXPANSION_OBJ = $(addprefix $(OBJ_DIR)/,$(EXPANSION_SRC:.c=.o))

OBJ += $(EXPANSION_OBJ)


#	PARSING

PARSE_DIR = $(SRC_DIR)/parser

PARSE_SRC = parser.c retrieve_word_list.c create_env_table.c create_token.c tok_len_scan_list.c \
add_boundry_to_list.c build_word.c create_cmd_list.c

PARSE_OBJ = $(addprefix $(OBJ_DIR)/,$(PARSE_SRC:.c=.o))

OBJ += $(PARSE_OBJ)

#	FREE FUNCTIONS

FREE_DIR = $(SRC_DIR)/free_functions

FREE_SRC = free_scan_list.c free_word_list.c

FREE_OBJ = $(addprefix $(OBJ_DIR)/,$(FREE_SRC:.c=.o))

OBJ += $(FREE_OBJ)

#	BUILT-INS

BUILTINS_DIR = $(SRC_DIR)/builtins

BUILTINS_SRC = built_in.c ft_cd.c ft_echo.c ft_exit.c ft_pwd.c

BUILTINS_OBJ = $(addprefix $(OBJ_DIR)/,$(BUILTINS_SRC:.c=.o))

OBJ += $(BUILTINS_OBJ)

#	EXECUTION

EXEC_DIR = $(SRC_DIR)/execution_src

EXEC_SRC = execution.c access_file.c single_cmd.c multiple_cmd.c get_cmd.c \
get_path.c open_dup2.c errors.c child_process.c

EXEC_OBJ = $(addprefix $(OBJ_DIR)/,$(EXEC_SRC:.c=.o))

OBJ += $(EXEC_OBJ)

#	MAIN OBJ

OBJ += $(MAIN_OBJ)
