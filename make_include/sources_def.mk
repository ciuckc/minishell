include make_include/general_def.mk

#	Template for adding different directories with source file
#	
#	#	EXAMPLE
#	EXAMPLE_DIR = $(SRC_DIR)/example
#	EXAMPLE_SRC = source1.c source2.c source3.c ...
#	EXAMPLE_OBJ = $(addprefix $(OBJ_DIR)/,$(EXAMPLE_SRC:.c=.o))
#	OBJ += $(EXAMPLE_OBJ)

#	PARSING

PARSE_DIR = $(SRC_DIR)/parser

PARSE_SRC = parser.c create_token_list.c

PARSE_OBJ = $(addprefix $(OBJ_DIR)/,$(PARSE_SRC:.c=.o))

EXEC_DIR = $(SRC_DIR)/execution_src

EXEC_SRC = access_file.c	errors.c		\
			execution.c		get_cmd.c  		\
			multiple_cmd.c	run_execution.c	\
			data_fetch.c	exec_single.c	\
			execution_start.c get_path.c	\
			open_dup2.c		single_cmd.c

EXEC_OBJ = $(addprefix $(OBJ_DIR)/,$(EXEC_SRC:.c=.o))

BUILTINS_DIR = $(SRC_DIR)/builtins

BUILTINS_SRC = built_in.c	ft_cd.c		ft_echo.c

BUILTINS_OBJ = $(addprefix $(OBJ_DIR)/,$(BUILTINS_SRC:.c=.o))

EXEC_UTILSDIR = $(SRC_DIR)/execution_utils

EXEC_UTILS_SRC = 	split_assist.c	ft_split.c	input.c	\
					lists_token.c 	
					
# ft_list_files.c

EXEC_UTILS_OBJ = $(addprefix $(OBJ_DIR)/,$(EXEC_UTILS_SRC:.c=.o))

OBJ = $(MAIN_OBJ) $(PARSE_OBJ) $(EXEC_OBJ) $(BUILTINS_OBJ) $(EXEC_UTILS_OBJ)
