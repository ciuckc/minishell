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

PARSE_SRC = parser.c

PARSE_OBJ = $(addprefix $(OBJ_DIR)/,$(PARSE_SRC:.c=.o))

OBJ = $(MAIN_OBJ) $(PARSE_OBJ)