NAME = hashmap.a

SRC = init_table.c insert_in_table.c remove_item.c hash_string.c item_search.c \
remove_all.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

AR = ar

AR_FLAGS = rcs

ARCHIVE = $(AR) $(AR_FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(ARCHIVE) $(NAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $^

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) -r $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re