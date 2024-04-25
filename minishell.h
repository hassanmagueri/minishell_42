/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:22:57 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/25 12:58:34 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell.h"
# include <unistd.h>

# include <sys/wait.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define ENV_LST 0
# define TOKEN_LST 1
// # define SEP " |"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	int		first;
	int		last;
	int		tub[2];
	int		infile;
	int		outfile;
	pid_t	pid;
	char	**env_path;
}	t_data;

typedef enum e_type
{
	APPEND,//>>
	HEARDOC,//<< 
	INPUT,// < 
	OUTPUT,// >
	WORD,
	SPACE,
	VAR,//$
	PIPE,//|
	SING_Q,//""
	DOUB_Q,//''
	EXIT_STATUS
}	t_type;

typedef struct s_redir
{
	char			*file_name;
	int				infile;
	int				outfile;
	int				input_fd;
	int				output_fd;
	t_type			redirection_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	struct s_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token //| > < >> << "" '' $VAR SPACE 
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}	t__lst_token;

typedef struct s_var
{
	int	start;
	int	end;
}	t_var;

typedef struct s_lst_env
{
	char				*key;
	char				*value;
	struct s_lst_env	*next;
}	t_lst_env;
// token
int				ft_join(t__lst_token **lst_token);
t__lst_token	*ft_new_token(char *str, t_type type);
void			ft_lst_token_add_back(t__lst_token **lst, t__lst_token *token);
t__lst_token	*ft__lst_token_last(t__lst_token *lst);
int				ft__lst_tokenize(t__lst_token **token, char *cmd);
int				is_sep(int c);
void			print__lst_tokens(t__lst_token *lst);
char			*ft_strnjoin(char const *s1, char const *s2, unsigned int n);
//errors
int				print_error(char *msg);
int				generate_errors(t__lst_token **tokens);

// env
int				init_env(t_lst_env **lst, char **env);
int				ft_lst_remove_env(t_lst_env **lst_env, char *key);
int				ft_lst_add_back_env(t_lst_env **lst_env, t_lst_env *node_env);
void			print_lst_env(t_lst_env *lst);
char			*ft_get_env_val(t_lst_env **lst_env, char	*key);
t_lst_env		*ft_get_env(t_lst_env **lst_env, char	*key);
t_lst_env		*ft_new_env(char *key, char *value);
t_lst_env		*ft_lst_env_last(t_lst_env *lst);
//
//expend
int				ft_expand(t__lst_token **lst_token, t_lst_env **lst_env);
//
//excution
void			ft_lst_cmd(t_lst_env *lst, t_cmd *args, t_data *pip);
//

//ft_cmd
int				ft_cmd(t_cmd **cmd, t__lst_token **tokens);
int				index_of(char *str, char c);
int				ft_strlen(const char *str);
int				ft_isdigit(int c);
int				ft_toupper(int c);
char			**ft_split(char *s, char c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strnstr(char *haystack, char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
// char	**split(char *s, char c);

// int ft_heredoc(t__lst_token **lst_token);

#endif
