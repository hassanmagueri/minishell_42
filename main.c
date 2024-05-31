/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/31 21:25:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var;

void	ft_close_heredoc_files(t_cmd **lst_cmd)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = *lst_cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->redirection_type == HEARDOC)
				close(ft_atoi(redir->file_name));
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	generate_input(t_lst_env **lst_env, t_data *pip, int *ex_state)
{
	int			pase_res;
	char		*input;
	t_cmd		*cmd;
	t_lst_token	*lst_token;

	signal(SIGINT, handle_c_slash_ctrol);
	signal(SIGQUIT, handle_c_slash_ctrol);
	(1) && (lst_token = NULL, cmd = NULL);
	input = readline("~ minishell 😎 ↪ ");
	if (g_var == 1)
		*ex_state = 1;
	if (input == NULL)
	{
		gc_alloc(0, FREE);
		gc_alloc(0, FREE_ENV);
		return (ft_putendl_fd("exit", 1), exit(*ex_state), 1);
	}
	if (input[0] == '\0')
		return (free(input), 0);
	add_history(input);
	ft_lst_tokenize(&lst_token, input);
	free(input);
	pase_res = ft_parsing(&lst_token, lst_env, &cmd, ex_state);
	if (pase_res)
		return (*ex_state = pase_res, 1);
	ft_check_cmd(cmd, lst_env, pip, ex_state);
	return (ft_close_heredoc_files(&cmd), 1);
}

int	main(int argc, char *argv[], char **env)
{
	int			ex_state;
	t_data		pip;
	t_lst_env	*lst_env;

	g_var = 0;
	lst_env = NULL;
	if (argc > 1)
		return ((void)argv, 1);
	init_env(&lst_env, env);
	init_path_env(&pip, &lst_env);
	rl_catch_signals = 0;
	ex_state = 0;
	while (1 && isatty(STDIN_FILENO))
	{
		generate_input(&lst_env, &pip, &ex_state);
		g_var = 0;
		gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}
