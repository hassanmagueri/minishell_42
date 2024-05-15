/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/15 21:49:09 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
	char *input;
	int	exit_state;
	t_lst_env *lst_env;
	t_lst_env *last_lst;
	t_data pip;

	exit_state = 0;
	lst_env = NULL;
	pip.env = env;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	// init_path_env(&pip,lst_env);
	init_path_env(&pip,lst_env,env);
	signal(SIGINT, handle_c_slash_ctrol);
    signal(SIGQUIT, handle_c_slash_ctrol);
	rl_catch_signals = 0;
	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		// input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		input = readline("minishell 😎 : ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input[0]=='\0')
			continue;
		add_history(input);
		ft__lst_tokenize(&t, input);
		int n = generate_errors(&t);
		// print__lst_tokens(t);
		ft_expand(&t, &lst_env, exit_state);
		// continue;
		printf("----------------------------------------------------\n");
		print__lst_tokens(t);
		ft_join(&t);
		ft_heredoc(&t, &lst_env);
		if (n) 
			continue;
		ft_cmd(&cmd, &t);
		print_lst_cmd(&cmd);
		ft_chech_excut_cmd(cmd,lst_env,&pip);
		// exit_state = cmd->exit_status;
		free(input);
		// gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}
