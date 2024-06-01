CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(READLINE_INCLUDE)
SRC_DIR = .
OBJ_DIR = obj
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
LDFLAGS = -L$(READLINE_LIB) -lreadline 
SRC_FILES = parsing/error.c parsing/expend.c parsing/expend_utils.c parsing/expend_utils_1.c \
			parsing/heredoc.c parsing/heredoc_utils.c parsing/join.c \
			parsing/lst_cmd.c parsing/lst_cmd_utils.c parsing/lst_token.c  parsing/lst_token_utils.c \
			parsing/parsing.c parsing/tokenizataion.c parsing/tokenizataion_utils.c \
			garbage_collector/malloc.c garbage_collector/malloc_utils.c \
			builtins/cd.c builtins/cd_utils.c builtins/echo.c builtins/env.c  builtins/exit.c \
			builtins/exit_utils.c builtins/export.c builtins/export_utils.c builtins/export_utils1.c \
			builtins/export_utils2.c builtins/ft_split_s_tab.c builtins/lst_env.c builtins/lst_env_utils.c \
			builtins/pwd.c builtins/unset.c \
			execution/binary_command.c execution/excut_cmdline.c  execution/pipe.c execution/redirection.c \
			execution/utils.c execution/binary_command_utils.c execution/ft_execut.c execution/pipe_utils.c execution/signal.c execution/ft_last_cmd.c \
			utils/ft_atoi.c utils/ft_bzero.c utils/ft_calloc.c utils/ft_isalnum.c utils/ft_isdigit.c utils/ft_itoa.c utils/ft_putchar_fd.c utils/ft_putendl_fd.c \
			utils/ft_putstr_fd.c utils/ft_split.c utils/ft_split_ws.c utils/ft_strchr.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c \
			utils/ft_strncmp.c utils/ft_strtrim.c utils/ft_substr.c \
			utils/ft_strnjoin.c main.c\

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c minishell.h| $(OBJ_DIR)/subdirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/subdirs:
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/garbage_collector
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/execution

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
