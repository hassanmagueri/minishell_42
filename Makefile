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

CC = cc -g -fsanitize=address
CFLAGS = #-Wall -Wextra -Werror 
SRC_DIR = .
OBJ_DIR = obj

# SRC_FILES = $(wildcard *.c)
SRC_FILES = lst_token.c ft_strnjoin.c  \
			main.c tokenizataion.c lst_env.c expend.c \
			error.c lst_cmd.c join.c pipe/excut_binary_cmd.c pipe/ft_pipeline.c pipe/excuction.c \
			builtins/cd.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c \
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

$(OBJ_DIR)/%.o: pipe/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXECUTABLE) $(TXT_FILES)

re: fclean all
