CC = gcc
CFLAGS = -MMD -Wall -Wextra -Werror -g3
SRC =	./main.c

NAME= random_test

OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(DEP)

fclean:
	make clean -C .
	rm -rf $(NAME)

re:
	make fclean -C .
	make all -C .

-include $(DEP)% 