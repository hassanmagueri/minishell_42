CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(READLINE_INCLUDE) #-g -fsanitize=address
SRC_DIR = .
OBJ_DIR = obj
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
# CFLAGS += -I$(READLINE_INCLUDE) #-g -fsanitize=addressmake
LDFLAGS = -L$(READLINE_LIB) -lreadline 
SRC_FILES = parsing/error.c parsing/expend.c parsing/expend_utils.c parsing/expend_utils_1.c \
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
			libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
			libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_lstadd_back_bonus.c libft/ft_lstadd_front_bonus.c \
			libft/ft_lstclear_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstiter_bonus.c libft/ft_lstlast_bonus.c libft/ft_lstmap_bonus.c \
			libft/ft_lstnew_bonus.c libft/ft_lstsize_bonus.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c \
			libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c \
			libft/ft_split_ws.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c \
			libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c\
			libft/ft_tolower.c libft/ft_toupper.c \
			ft_strnjoin.c main.c\

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c| $(OBJ_DIR)/subdirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/subdirs:
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/garbage_collector
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/execution

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
