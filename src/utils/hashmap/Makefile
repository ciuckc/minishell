NAME = hashmap.a

SRC = init_table.c insert_in_table.c remove_item.c hash_string.c

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

main:
	$(CC) $(FLAGS) -fsanitize=address -g main.c $(NAME) ../libft/libft.a

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) -r $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re