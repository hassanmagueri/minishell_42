NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC =  main.c
OBJ_DIR = obj


OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c minishell.h | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all