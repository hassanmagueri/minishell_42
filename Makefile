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

CC = cc #-g -fsanitize=address
CFLAGS = #-Wall -Wextra -Werror 
SRC_DIR = .
OBJ_DIR = obj
CFLAGS = -I$(READLINE_INCLUDE) -g -fsanitize=address   # Add Readline include path
LDFLAGS = -L$(READLINE_LIB) -lreadline 
# SRC_FILES = $(wildcard *.c)
SRC_FILES = ft_strnjoin.c  \
			main.c \

READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

PARS_FILES = $(wildcard parsing/*.c)
PARS_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(PARS_FILES:.c=.o)))

GC_FILES = $(wildcard garbage_collector/*.c)
GC_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(GC_FILES:.c=.o)))

LIBFT_FILES = $(wildcard libft/*.c)
LIBFT_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT_FILES:.c=.o)))

BUILT_FILES = $(wildcard builtins/*.c)
BUILT_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(BUILT_FILES:.c=.o)))

EXECU_FILES = $(wildcard execution/*.c)
EXECU_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(EXECU_FILES:.c=.o)))
 
EXECUTABLE = minishell
TXT_FILES = a.out

.PHONY: all clean fclean re


all: $(EXECUTABLE)

$(EXECUTABLE): $(LIBFT_OBJ_FILES) $(GC_OBJ_FILES) $(BUILT_OBJ_FILES) $(OBJ_FILES) $(PARS_OBJ_FILES) $(EXECU_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: builtins/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: garbage_collector/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: parsing/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: execution/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXECUTABLE) $(TXT_FILES)

re: fclean all
