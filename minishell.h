/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:22:57 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:28:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell.h"
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define ENV_LST 0
# define TOKEN_LST 1

extern int	g_var;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	int		first;
	char	**env;
	int		last;
	int		tub[2];
	int		infile;
	int		outfile;
	char	**env_path;
	int		input_fd;
	pid_t	*pids;
	int		pid_index;
	int		num_cmds;
}	t_data;

typedef enum e_type
{
	APPEND,
	HEARDOC,
	INPUT,
	OUTPUT,
	WORD,
	WSP,
	VAR,
	PIPE,
	SING_Q,
	DOUB_Q,
	EXIT_STATUS
}	t_type;

typedef enum e_gc_type
{
	ALLOC = 1,
	ALLOC_ENV = 2,
	FREE = 3,
	FREE_ENV = 4,
}	t_gc_type;

typedef struct s_redir
{
	char			*file_name;
	t_type			redirection_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_gc
{
	void		*content;
	int			alloc_for;
	struct s_gc	*next;
}	t_gc;

typedef struct s_cmd
{
	char			**cmd;
	int				len;
	int				exit_status;
	struct s_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
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

int				ft_join(t__lst_token **lst_token);
// heredoc
int				ft_heredoc(t__lst_token **lst_token, t_lst_env **lst_env);
char			*ft_get_delimiter(t__lst_token *token);
int				ft_fake_heredoc(t__lst_token **lst_token);
char			*ft_expand_var(char *input, t_lst_env **lst_env, int *index);
char			*ft_expend_input(char *input, t_lst_env **lst_env);
int				ft_buffering_fake_heredoc(t__lst_token *token);
int				ft_fake_heredoc(t__lst_token **lst_token);

// lst token
t__lst_token	*ft_new_token(char *str, t_type type);
t__lst_token	*ft__lst_token_last(t__lst_token **lst);
t__lst_token	*ft_get_token_by_type(t__lst_token **lst_token, t_type type);
t__lst_token	*ft_get_next_token_by_type(t__lst_token **lst_token,
					t_type type);
t__lst_token	*ft_next_token(t__lst_token **token);
void			ft_lst_token_add_back(t__lst_token **lst, t__lst_token *token);
int				ft_is_with_spaces(int c);
int				is_sep(int c);
int				find_sec(char *s, char c);
int				ft__lst_tokenize(t__lst_token **token, char *cmd);
int				is_sep(int c);
int				ft_token_redir(t__lst_token **token, char *input);
void			print__lst_tokens(t__lst_token *lst);
//parsing
int				ft_parsing(t__lst_token **lst_token, t_lst_env **lst_env,
					t_cmd **lst_cmd, int *exit_status);
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
char			*ft_handle_simple_string(char *old_output, char *new_output,
					int *index);
char			*ft_handle_var(t_lst_env **lst_env, char *key, int *index);
int				ft_expand(t__lst_token **lst_token,
					t_lst_env **lst_env, int *exit_state);
int				ft_expand_vars(t__lst_token **lst_token, t_lst_env **lst_env,
					t__lst_token **cur_pointer, t__lst_token *prev);
char			*ft_expand_in_doub_q(t_lst_env **lst_env,
					char *str, int exit_state);
void			ft_skip_delimiter(t__lst_token **cur_pointer);
char			*ft_handle_var(t_lst_env **lst_env, char *key, int *index);
char			*ft_first_cmd(t__lst_token **lst_token);
int				ft_is_endl_with_with_space(char *str);
int				ft_is_strong_word_befor(t__lst_token **lst_token,
					t__lst_token *last);
void			ft_add_wsp_middle(t__lst_token **cur_pointer);
t__lst_token	*ft_add_wsp_before(t__lst_token **cur_pointer);
//
//execution
//binry
void			ft_signal_ignore(void);
void			ft_default_signal(void);
int				ft_dup_close_infile(int infile);
void			ft_setup_pipeline(t_data *pip);
void			ft_update_pipeline_fds(t_data *pip);
char			*find_path_executable(char **env_path, char *cmd);
int				ft_execute_command(t_data *pip, t_lst_env **lst, char **cmd);
int				parsing_cmd(char *str);
int				error_msg_cmd(char *str, int i);
char			**ft_lst_to_tab(t_lst_env **lst);
int				len_lst(t_lst_env *lst);
int				is_directory(char *path);
char			*ft_str_env(char *s1, char *s2);
///  
int				ft_excut_cmd_line(t_lst_env **lst, t_cmd *args,
					t_data *pip, int *ex_state);
int				ft_check_buitin_cmd(t_cmd	*args);
void			ft_lst_cmd(t_cmd *command, t_lst_env **lst,
					t_data *pip, int *exit_state);
void			ft_check_cmd(t_cmd	*command, t_lst_env **lst,
					t_data *pip, int *ex_state);
void			ft_excut_child(t_cmd *args, t_data *pip,
					t_lst_env **lst, int *ex_state);
void			ft_redirection(t_cmd *cmd, t_data *pip);
void			handle_c_slash_ctrol(int signal);
void			init_path_env(t_data *pip, t_lst_env **lst);

// garbage collector 
t_gc			*ft_gclast(t_gc **lst);
t_gc			*ft_gcnew(void *content, int alloc_for);
void			*gc_alloc(size_t size, t_gc_type type);
void			ft_gcfree_node(t_gc *node);
void			ft_gcadd_back(t_gc **lst, t_gc *new);

int				ft_cmd_bui_child(t_lst_env **lst, t_cmd *args,
					t_data *pip, int *ex_state);
// builtin
//\\cd
int				ft_change_directory(t_lst_env *lst, char *pwd, char *args);
char			*ft_get_newpwd_path(char *pwd);
int				ft_check_value_node(t_lst_env **lst_env, char *key);
int				ft_change_value_lst(t_lst_env **lst_env,
					char *key, char *value);
int				ft_cd(t_lst_env **lst, t_cmd *args);
int				ft_change_value_dir(t_lst_env **lst, char *pwd,
					char *oldpwd, char *str);
char			*ft_get_pwd(t_lst_env **lst, char *pwd,
					char *oldpwd, char *cmd);
int				ft_chdir_oldpwd(t_lst_env **lst);
int				ft_not_access_parent(t_lst_env **lst, char *str, char *pwd);
void			error_msg(void);
///
// export 
int				ft_export(t_lst_env **lst_env, t_cmd *str);
void			print_lst_export(t_lst_env *lst);
int				index_key(char *str, char c);
int				ft_check_lst_key(t_lst_env **lst, char *key);
int				ft_prasing_export(char *str);
void			ft_add_val(t_lst_env **lst, char *key, char *val);
char			*ft_join_value_lst(char *s1, char *s2, t_gc_type type);
int				ft_strcmp(char *s1, char *s2);
void			print_lst_order_alpha(t_lst_env **lst);
void			ft_change_val(t_lst_env **lst, char *key, char *value);
int				error_msg_export(char *str);
char			*ft_value(char *value, int len, char *str);
char			*ft_key(char *key, int len, char *str);
void			ft_update_lst(t_lst_env **lst_env, char *key,
					char *value, char *str);
///
int				ft_echo(t_cmd *cmd);
int				ft_pwd(void);
int				ft_unset(t_lst_env **lst, t_cmd *args);
int				ft_env(t_lst_env **lst, t_cmd *args);
/// exit
int				ft_exit(t_cmd *args, int *ex_state);
char			*ft_skip_zero(char *str);
int				ft_parsing_exit(char *str);
int				error_msg_exit(char *str, int i);
/////
char			*ft_handle_var(t_lst_env **lst_env,
					char *old_output, int *index);
//ft_cmd
int				ft_cmd(t_cmd **cmd, t__lst_token **tokens);
t_redir			*ft_new_redir(char *file_name, t_type redirection_type);
int				ft_add_back_redir(t_redir **redirs, t_redir *cmd);
t_cmd			*ft_new_cmd(char **cmd, t_redir *redir);
int				ft_add_back_cmd(t_cmd **cmds, t_cmd *cmd);
int				ft_len_cmd_part(t__lst_token **tokens);
void			print_lst_cmd(t_cmd **cmd);//
//
int				ft_dup_and_close(int file, int i);
int				ft_dup_and_close_outfile(int outfile, int i);
void			handle_heredoc(int signal);
char			**ft_split_space_tab(char *str, int type);
//libft
int				index_of(char *str, char c);
int				ft_strlen(const char *str);
int				ft_isdigit(int c);
int				ft_toupper(int c);
char			**ft_split(char *s, char c, int type);
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
char			*ft_strdup(const char *s1, int type);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size, int type);
char			*ft_substr(char const *s, unsigned int start,
					size_t len, int type);
char			*ft_strjoin(char const *s1, char const *s2, t_gc_type type);
char			*ft_strnjoin(char const *s1, char const *s2, unsigned int n,
					t_gc_type type);
char			*ft_strtrim(char const *s1, char const *set, int type);
char			*ft_itoa(int n, t_gc_type type);
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
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
char			**ft_split_ws(char *str, t_gc_type type);
#endif
