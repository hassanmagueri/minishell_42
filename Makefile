CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
SRC_DIR = .
OBJ_DIR = obj
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
CFLAGS += -I$(READLINE_INCLUDE) -g -fsanitize=address
LDFLAGS = -L$(READLINE_LIB) -lreadline 
SRC_FILES = ft_strnjoin.c parsing/error.c parsing/expend.c parsing/expend_utils.c parsing/expend_utils_1.c \
			parsing/heredoc.c parsing/heredoc_utils.c parsing/join.c \
			parsing/lst_cmd.c parsing/lst_cmd_utils.c parsing/lst_token.c  parsing/lst_token_utils.c \
			parsing/parsing.c parsing/tokenizataion.c parsing/tokenizataion_utils.c \
			garbage_collector/malloc.c garbage_collector/malloc_utils.c\
			builtins/cd.c builtins/cd_utils.c builtins/echo.c builtins/env.c  builtins/exit.c\
			builtins/exit_utils.c builtins/export.c builtins/export_utils.c builtins/export_utils1.c \
			builtins/export_utils2.c builtins/ft_split_s_tab.c builtins/lst_env.c builtins/lst_env_utils.c \
			builtins/pwd.c builtins/unset.c\
			execution/binary_command.c execution/excut_cmdline.c  execution/pipe.c execution/redirection.c \
			execution/utils.c execution/binary_command_utils.c execution/ft_execut.c execution/pipe_utils.c execution/signal.c\
			main.c\

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
LIBFT_FILES = $(wildcard libft/*.c)
LIBFT_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT_FILES:.c=.o)))
NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT_OBJ_FILES) $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/subdirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/%.c | $(OBJ_DIR)/subdirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/subdirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/garbage_collector
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/execution

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
