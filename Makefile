# NAME = minishell
# CC = cc
# FLAGS = -Wall -Wextra -Werror
# RM = rm -rf

# SRC =  main.c
# OBJ_DIR = obj


# OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# all : $(NAME)

# $(NAME) : $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

# $(OBJ_DIR)/%.o : %.c minishell.h | $(OBJ_DIR)
# 	$(CC) $(FLAGS) -c $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

# clean:
# 	$(RM) $(OBJ_DIR)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRC_DIR = .
OBJ_DIR = obj

# SRC_FILES = $(wildcard *.c)
SRC_FILES = ft_split_cmd.c lst_token.c ft_strnjoin.c  main.c tokenizataion.c
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
LIBFT_FILES = $(wildcard libft/*.c)
LIBFT_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT_FILES:.c=.o)))

EXECUTABLE = minishell
TXT_FILES = a.out

.PHONY: all clean fclean re

all: $(EXECUTABLE)
# all:
# 	echo $(OBJ_FILES)

$(EXECUTABLE): $(LIBFT_OBJ_FILES) $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXECUTABLE) $(TXT_FILES)

fclean: clean

re: fclean all
