/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 10:23:38 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var;

int	generate_input(t_lst_env **lst_env, t_data *pip, int *ex_state)
{
	int				pase_res;
	char			*input;
	t_cmd			*cmd;
	t__lst_token	*lst_token;

	(1) && (lst_token = NULL, cmd = NULL);
	signal(SIGINT, handle_c_slash_ctrol);
	signal(SIGQUIT, handle_c_slash_ctrol);
	input = readline("~ minishell 😎 ↪ ");
	if (input == NULL)
		exit(printf("exit\n"));
	if (input[0] == '\0')
		return (0);
	if (g_var == 1)
		*ex_state = 1;
	add_history(input);
	ft__lst_tokenize(&lst_token, input);
	pase_res = ft_parsing(&lst_token, lst_env, &cmd, ex_state);
	if (pase_res)
		return (*ex_state = pase_res, 1);
	ft_check_cmd(cmd, lst_env, pip, ex_state);
	free(input);
	g_var = 0;
	return (1);
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
		gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}
