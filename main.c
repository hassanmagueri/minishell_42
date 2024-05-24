/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/24 22:14:52 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int exit_status ;

int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	t_lst_env *last_lst;
	t_data pip;

	exit_status = 0;
	lst_env = NULL;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	
	init_env(&lst_env, env);
	init_path_env(&pip,&lst_env);
	rl_catch_signals = 0;
	while (1 && isatty(STDIN_FILENO))
	{
		t__lst_token *lst_token = NULL;
		t_cmd *cmd = NULL;
		signal(SIGINT, handle_c_slash_ctrol);
    	signal(SIGQUIT, handle_c_slash_ctrol);
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		// input = readline("~ minishell 😎 ↪ ");
		if (input == NULL)
		{
			printf("exit\n");	
			exit(0);
		}
		if (input[0]=='\0')
			continue;
		add_history(input);
		ft__lst_tokenize(&lst_token, input);
		exit_status = ft_parsing(&lst_token, &lst_env, &cmd, exit_status);
		ft_chech_excut_cmd(cmd,&lst_env,&pip);
		exit_status = cmd->exit_status;
		if (exit_status == 1)
			cmd->exit_status = 1;
			// printf("exit status == %d\n",exit_status);
		free(input);
		//gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}
