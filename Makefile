CC = gcc
CFLAGS = #-Wall -Wextra -Werror -g -fsanitize=address
SRC_DIR = .
OBJ_DIR = obj

# SRC_FILES = $(wildcard *.c)
SRC_FILES = ft_split_cmd.c lst_token.c ft_strnjoin.c  main.c tokenizataion.c lst_env.c expend.c
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

fclean: clean
	rm -f $(EXECUTABLE) $(TXT_FILES)

re: fclean all
